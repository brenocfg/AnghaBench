#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_10__ {int options; TYPE_3__* session; } ;
struct TYPE_8__ {scalar_t__ ticklen; } ;
struct TYPE_9__ {scalar_t__ ssl_version; TYPE_2__ ext; TYPE_1__* cipher; } ;
struct TYPE_7__ {int /*<<< orphan*/  algorithm2; } ;
typedef  TYPE_4__ SSL ;
typedef  int /*<<< orphan*/  EXT_RETURN ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 scalar_t__ EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EXT_RETURN_FAIL ; 
 int /*<<< orphan*/  EXT_RETURN_NOT_SENT ; 
 int /*<<< orphan*/  EXT_RETURN_SENT ; 
 size_t F5_WORKAROUND_MAX_MSG_LEN ; 
 size_t F5_WORKAROUND_MIN_MSG_LEN ; 
 scalar_t__ PSK_PRE_BINDER_OVERHEAD ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_CTOS_PADDING ; 
 int SSL_OP_TLSEXT_PADDING ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TLS1_3_VERSION ; 
 int /*<<< orphan*/  TLSEXT_TYPE_padding ; 
 int /*<<< orphan*/  WPACKET_get_total_written (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_sub_allocate_bytes_u16 (int /*<<< orphan*/ *,size_t,unsigned char**) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * ssl_md (int /*<<< orphan*/ ) ; 

EXT_RETURN tls_construct_ctos_padding(SSL *s, WPACKET *pkt,
                                      unsigned int context, X509 *x,
                                      size_t chainidx)
{
    unsigned char *padbytes;
    size_t hlen;

    if ((s->options & SSL_OP_TLSEXT_PADDING) == 0)
        return EXT_RETURN_NOT_SENT;

    /*
     * Add padding to workaround bugs in F5 terminators. See RFC7685.
     * This code calculates the length of all extensions added so far but
     * excludes the PSK extension (because that MUST be written last). Therefore
     * this extension MUST always appear second to last.
     */
    if (!WPACKET_get_total_written(pkt, &hlen)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CTOS_PADDING,
                 ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }

    /*
     * If we're going to send a PSK then that will be written out after this
     * extension, so we need to calculate how long it is going to be.
     */
    if (s->session->ssl_version == TLS1_3_VERSION
            && s->session->ext.ticklen != 0
            && s->session->cipher != NULL) {
        const EVP_MD *md = ssl_md(s->session->cipher->algorithm2);

        if (md != NULL) {
            /*
             * Add the fixed PSK overhead, the identity length and the binder
             * length.
             */
            hlen +=  PSK_PRE_BINDER_OVERHEAD + s->session->ext.ticklen
                     + EVP_MD_size(md);
        }
    }

    if (hlen > F5_WORKAROUND_MIN_MSG_LEN && hlen < F5_WORKAROUND_MAX_MSG_LEN) {
        /* Calculate the amount of padding we need to add */
        hlen = F5_WORKAROUND_MAX_MSG_LEN - hlen;

        /*
         * Take off the size of extension header itself (2 bytes for type and
         * 2 bytes for length bytes), but ensure that the extension is at least
         * 1 byte long so as not to have an empty extension last (WebSphere 7.x,
         * 8.x are intolerant of that condition)
         */
        if (hlen > 4)
            hlen -= 4;
        else
            hlen = 1;

        if (!WPACKET_put_bytes_u16(pkt, TLSEXT_TYPE_padding)
                || !WPACKET_sub_allocate_bytes_u16(pkt, hlen, &padbytes)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CTOS_PADDING,
                     ERR_R_INTERNAL_ERROR);
            return EXT_RETURN_FAIL;
        }
        memset(padbytes, 0, hlen);
    }

    return EXT_RETURN_SENT;
}