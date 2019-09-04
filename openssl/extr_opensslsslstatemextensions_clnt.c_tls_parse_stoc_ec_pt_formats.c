#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_8__ {TYPE_2__* session; int /*<<< orphan*/  hit; } ;
struct TYPE_6__ {size_t ecpointformats_len; int /*<<< orphan*/ * ecpointformats; } ;
struct TYPE_7__ {TYPE_1__ ext; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  PACKET_as_length_prefixed_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_copy_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 size_t PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_STOC_EC_PT_FORMATS ; 
 int /*<<< orphan*/  SSL_R_BAD_EXTENSION ; 
 int /*<<< orphan*/  SSL_R_BAD_LENGTH ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tls_parse_stoc_ec_pt_formats(SSL *s, PACKET *pkt, unsigned int context,
                                 X509 *x, size_t chainidx)
{
    size_t ecpointformats_len;
    PACKET ecptformatlist;

    if (!PACKET_as_length_prefixed_1(pkt, &ecptformatlist)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_STOC_EC_PT_FORMATS,
                 SSL_R_BAD_EXTENSION);
        return 0;
    }
    if (!s->hit) {
        ecpointformats_len = PACKET_remaining(&ecptformatlist);
        if (ecpointformats_len == 0) {
            SSLfatal(s, SSL_AD_DECODE_ERROR,
                     SSL_F_TLS_PARSE_STOC_EC_PT_FORMATS, SSL_R_BAD_LENGTH);
            return 0;
        }

        s->session->ext.ecpointformats_len = 0;
        OPENSSL_free(s->session->ext.ecpointformats);
        s->session->ext.ecpointformats = OPENSSL_malloc(ecpointformats_len);
        if (s->session->ext.ecpointformats == NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_PARSE_STOC_EC_PT_FORMATS, ERR_R_INTERNAL_ERROR);
            return 0;
        }

        s->session->ext.ecpointformats_len = ecpointformats_len;

        if (!PACKET_copy_bytes(&ecptformatlist,
                               s->session->ext.ecpointformats,
                               ecpointformats_len)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_PARSE_STOC_EC_PT_FORMATS, ERR_R_INTERNAL_ERROR);
            return 0;
        }
    }

    return 1;
}