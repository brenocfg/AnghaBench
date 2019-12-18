#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_11__ {scalar_t__ ticklen; int tick_lifetime_hint; int /*<<< orphan*/  tick; scalar_t__ tick_age_add; } ;
struct TYPE_14__ {scalar_t__ ssl_version; TYPE_2__ ext; TYPE_1__* cipher; scalar_t__ time; } ;
struct TYPE_12__ {scalar_t__ tick_identity; } ;
struct TYPE_13__ {scalar_t__ hello_retry_request; scalar_t__ psksession_id_len; TYPE_6__* psksession; TYPE_6__* session; TYPE_3__ ext; int /*<<< orphan*/  psksession_id; } ;
struct TYPE_10__ {int /*<<< orphan*/  algorithm2; } ;
typedef  TYPE_4__ SSL ;
typedef  int /*<<< orphan*/  EXT_RETURN ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 size_t EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EXT_RETURN_FAIL ; 
 int /*<<< orphan*/  EXT_RETURN_NOT_SENT ; 
 int /*<<< orphan*/  EXT_RETURN_SENT ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_CTOS_PSK ; 
 scalar_t__ SSL_HRR_PENDING ; 
 int /*<<< orphan*/  SSL_R_BAD_PSK ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TLS1_3_VERSION ; 
 int /*<<< orphan*/  TLSEXT_TYPE_psk ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_fill_lengths (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_get_curr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_get_total_written (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_sub_allocate_bytes_u8 (int /*<<< orphan*/ *,size_t,unsigned char**) ; 
 int /*<<< orphan*/  WPACKET_sub_memcpy_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * ssl_handshake_md (TYPE_4__*) ; 
 int /*<<< orphan*/ * ssl_md (int /*<<< orphan*/ ) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int tls_psk_do_binder (TYPE_4__*,int /*<<< orphan*/  const*,unsigned char*,size_t,int /*<<< orphan*/ *,unsigned char*,TYPE_6__*,int,int) ; 

EXT_RETURN tls_construct_ctos_psk(SSL *s, WPACKET *pkt, unsigned int context,
                                  X509 *x, size_t chainidx)
{
#ifndef OPENSSL_NO_TLS1_3
    uint32_t now, agesec, agems = 0;
    size_t reshashsize = 0, pskhashsize = 0, binderoffset, msglen;
    unsigned char *resbinder = NULL, *pskbinder = NULL, *msgstart = NULL;
    const EVP_MD *handmd = NULL, *mdres = NULL, *mdpsk = NULL;
    int dores = 0;

    s->ext.tick_identity = 0;

    /*
     * Note: At this stage of the code we only support adding a single
     * resumption PSK. If we add support for multiple PSKs then the length
     * calculations in the padding extension will need to be adjusted.
     */

    /*
     * If this is an incompatible or new session then we have nothing to resume
     * so don't add this extension.
     */
    if (s->session->ssl_version != TLS1_3_VERSION
            || (s->session->ext.ticklen == 0 && s->psksession == NULL))
        return EXT_RETURN_NOT_SENT;

    if (s->hello_retry_request == SSL_HRR_PENDING)
        handmd = ssl_handshake_md(s);

    if (s->session->ext.ticklen != 0) {
        /* Get the digest associated with the ciphersuite in the session */
        if (s->session->cipher == NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CTOS_PSK,
                     ERR_R_INTERNAL_ERROR);
            return EXT_RETURN_FAIL;
        }
        mdres = ssl_md(s->session->cipher->algorithm2);
        if (mdres == NULL) {
            /*
             * Don't recognize this cipher so we can't use the session.
             * Ignore it
             */
            goto dopsksess;
        }

        if (s->hello_retry_request == SSL_HRR_PENDING && mdres != handmd) {
            /*
             * Selected ciphersuite hash does not match the hash for the session
             * so we can't use it.
             */
            goto dopsksess;
        }

        /*
         * Technically the C standard just says time() returns a time_t and says
         * nothing about the encoding of that type. In practice most
         * implementations follow POSIX which holds it as an integral type in
         * seconds since epoch. We've already made the assumption that we can do
         * this in multiple places in the code, so portability shouldn't be an
         * issue.
         */
        now = (uint32_t)time(NULL);
        agesec = now - (uint32_t)s->session->time;
        /*
         * We calculate the age in seconds but the server may work in ms. Due to
         * rounding errors we could overestimate the age by up to 1s. It is
         * better to underestimate it. Otherwise, if the RTT is very short, when
         * the server calculates the age reported by the client it could be
         * bigger than the age calculated on the server - which should never
         * happen.
         */
        if (agesec > 0)
            agesec--;

        if (s->session->ext.tick_lifetime_hint < agesec) {
            /* Ticket is too old. Ignore it. */
            goto dopsksess;
        }

        /*
         * Calculate age in ms. We're just doing it to nearest second. Should be
         * good enough.
         */
        agems = agesec * (uint32_t)1000;

        if (agesec != 0 && agems / (uint32_t)1000 != agesec) {
            /*
             * Overflow. Shouldn't happen unless this is a *really* old session.
             * If so we just ignore it.
             */
            goto dopsksess;
        }

        /*
         * Obfuscate the age. Overflow here is fine, this addition is supposed
         * to be mod 2^32.
         */
        agems += s->session->ext.tick_age_add;

        reshashsize = EVP_MD_size(mdres);
        s->ext.tick_identity++;
        dores = 1;
    }

 dopsksess:
    if (!dores && s->psksession == NULL)
        return EXT_RETURN_NOT_SENT;

    if (s->psksession != NULL) {
        mdpsk = ssl_md(s->psksession->cipher->algorithm2);
        if (mdpsk == NULL) {
            /*
             * Don't recognize this cipher so we can't use the session.
             * If this happens it's an application bug.
             */
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CTOS_PSK,
                     SSL_R_BAD_PSK);
            return EXT_RETURN_FAIL;
        }

        if (s->hello_retry_request == SSL_HRR_PENDING && mdpsk != handmd) {
            /*
             * Selected ciphersuite hash does not match the hash for the PSK
             * session. This is an application bug.
             */
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CTOS_PSK,
                     SSL_R_BAD_PSK);
            return EXT_RETURN_FAIL;
        }

        pskhashsize = EVP_MD_size(mdpsk);
    }

    /* Create the extension, but skip over the binder for now */
    if (!WPACKET_put_bytes_u16(pkt, TLSEXT_TYPE_psk)
            || !WPACKET_start_sub_packet_u16(pkt)
            || !WPACKET_start_sub_packet_u16(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CTOS_PSK,
                 ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }

    if (dores) {
        if (!WPACKET_sub_memcpy_u16(pkt, s->session->ext.tick,
                                           s->session->ext.ticklen)
                || !WPACKET_put_bytes_u32(pkt, agems)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CTOS_PSK,
                     ERR_R_INTERNAL_ERROR);
            return EXT_RETURN_FAIL;
        }
    }

    if (s->psksession != NULL) {
        if (!WPACKET_sub_memcpy_u16(pkt, s->psksession_id,
                                    s->psksession_id_len)
                || !WPACKET_put_bytes_u32(pkt, 0)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CTOS_PSK,
                     ERR_R_INTERNAL_ERROR);
            return EXT_RETURN_FAIL;
        }
        s->ext.tick_identity++;
    }

    if (!WPACKET_close(pkt)
            || !WPACKET_get_total_written(pkt, &binderoffset)
            || !WPACKET_start_sub_packet_u16(pkt)
            || (dores
                && !WPACKET_sub_allocate_bytes_u8(pkt, reshashsize, &resbinder))
            || (s->psksession != NULL
                && !WPACKET_sub_allocate_bytes_u8(pkt, pskhashsize, &pskbinder))
            || !WPACKET_close(pkt)
            || !WPACKET_close(pkt)
            || !WPACKET_get_total_written(pkt, &msglen)
               /*
                * We need to fill in all the sub-packet lengths now so we can
                * calculate the HMAC of the message up to the binders
                */
            || !WPACKET_fill_lengths(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CTOS_PSK,
                 ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }

    msgstart = WPACKET_get_curr(pkt) - msglen;

    if (dores
            && tls_psk_do_binder(s, mdres, msgstart, binderoffset, NULL,
                                 resbinder, s->session, 1, 0) != 1) {
        /* SSLfatal() already called */
        return EXT_RETURN_FAIL;
    }

    if (s->psksession != NULL
            && tls_psk_do_binder(s, mdpsk, msgstart, binderoffset, NULL,
                                 pskbinder, s->psksession, 1, 1) != 1) {
        /* SSLfatal() already called */
        return EXT_RETURN_FAIL;
    }

    return EXT_RETURN_SENT;
#else
    return EXT_RETURN_NOT_SENT;
#endif
}