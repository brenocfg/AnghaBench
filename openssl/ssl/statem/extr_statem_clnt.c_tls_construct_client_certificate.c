#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_13__ {int cert_req; } ;
struct TYPE_14__ {TYPE_1__ tmp; } ;
struct TYPE_18__ {TYPE_5__* method; TYPE_3__* cert; TYPE_2__ s3; int /*<<< orphan*/  pha_context_len; int /*<<< orphan*/ * pha_context; } ;
struct TYPE_17__ {TYPE_4__* ssl3_enc; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* change_cipher_state ) (TYPE_6__*,int) ;} ;
struct TYPE_15__ {int /*<<< orphan*/ * key; } ;
typedef  TYPE_6__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int SSL3_CC_HANDSHAKE ; 
 int SSL3_CHANGE_CIPHER_CLIENT_WRITE ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_NO_ALERT ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_CLIENT_CERTIFICATE ; 
 scalar_t__ SSL_IS_FIRST_HANDSHAKE (TYPE_6__*) ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_6__*) ; 
 int /*<<< orphan*/  SSL_R_CANNOT_CHANGE_CIPHER ; 
 int /*<<< orphan*/  SSLfatal (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_sub_memcpy_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl3_output_cert_chain (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int) ; 

int tls_construct_client_certificate(SSL *s, WPACKET *pkt)
{
    if (SSL_IS_TLS13(s)) {
        if (s->pha_context == NULL) {
            /* no context available, add 0-length context */
            if (!WPACKET_put_bytes_u8(pkt, 0)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_TLS_CONSTRUCT_CLIENT_CERTIFICATE, ERR_R_INTERNAL_ERROR);
                return 0;
            }
        } else if (!WPACKET_sub_memcpy_u8(pkt, s->pha_context, s->pha_context_len)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_CLIENT_CERTIFICATE, ERR_R_INTERNAL_ERROR);
            return 0;
        }
    }
    if (!ssl3_output_cert_chain(s, pkt,
                                (s->s3.tmp.cert_req == 2) ? NULL
                                                           : s->cert->key)) {
        /* SSLfatal() already called */
        return 0;
    }

    if (SSL_IS_TLS13(s)
            && SSL_IS_FIRST_HANDSHAKE(s)
            && (!s->method->ssl3_enc->change_cipher_state(s,
                    SSL3_CC_HANDSHAKE | SSL3_CHANGE_CIPHER_CLIENT_WRITE))) {
        /*
         * This is a fatal error, which leaves enc_write_ctx in an inconsistent
         * state and thus ssl3_send_alert may crash.
         */
        SSLfatal(s, SSL_AD_NO_ALERT, SSL_F_TLS_CONSTRUCT_CLIENT_CERTIFICATE,
                 SSL_R_CANNOT_CHANGE_CIPHER);
        return 0;
    }

    return 1;
}