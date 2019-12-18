#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * confunc_f ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_7__ {int hand_state; } ;
struct TYPE_6__ {TYPE_2__ statem; } ;
typedef  TYPE_1__ SSL ;
typedef  TYPE_2__ OSSL_STATEM ;

/* Variables and functions */
 int SSL3_MT_CERTIFICATE ; 
 int SSL3_MT_CERTIFICATE_VERIFY ; 
 int SSL3_MT_CHANGE_CIPHER_SPEC ; 
 int SSL3_MT_CLIENT_HELLO ; 
 int SSL3_MT_CLIENT_KEY_EXCHANGE ; 
 int SSL3_MT_DUMMY ; 
 int SSL3_MT_END_OF_EARLY_DATA ; 
 int SSL3_MT_FINISHED ; 
 int SSL3_MT_KEY_UPDATE ; 
 int SSL3_MT_NEXT_PROTO ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_OSSL_STATEM_CLIENT_CONSTRUCT_MESSAGE ; 
 int /*<<< orphan*/  SSL_IS_DTLS (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_R_BAD_HANDSHAKE_STATE ; 
 int /*<<< orphan*/  SSLfatal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TLS_ST_CW_CERT 137 
#define  TLS_ST_CW_CERT_VRFY 136 
#define  TLS_ST_CW_CHANGE 135 
#define  TLS_ST_CW_CLNT_HELLO 134 
#define  TLS_ST_CW_END_OF_EARLY_DATA 133 
#define  TLS_ST_CW_FINISHED 132 
#define  TLS_ST_CW_KEY_EXCH 131 
#define  TLS_ST_CW_KEY_UPDATE 130 
#define  TLS_ST_CW_NEXT_PROTO 129 
#define  TLS_ST_PENDING_EARLY_DATA_END 128 
 int /*<<< orphan*/ * dtls_construct_change_cipher_spec ; 
 int /*<<< orphan*/ * tls_construct_cert_verify ; 
 int /*<<< orphan*/ * tls_construct_change_cipher_spec ; 
 int /*<<< orphan*/ * tls_construct_client_certificate ; 
 int /*<<< orphan*/ * tls_construct_client_hello ; 
 int /*<<< orphan*/ * tls_construct_client_key_exchange ; 
 int /*<<< orphan*/ * tls_construct_end_of_early_data ; 
 int /*<<< orphan*/ * tls_construct_finished ; 
 int /*<<< orphan*/ * tls_construct_key_update ; 
 int /*<<< orphan*/ * tls_construct_next_proto ; 

int ossl_statem_client_construct_message(SSL *s, WPACKET *pkt,
                                         confunc_f *confunc, int *mt)
{
    OSSL_STATEM *st = &s->statem;

    switch (st->hand_state) {
    default:
        /* Shouldn't happen */
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_OSSL_STATEM_CLIENT_CONSTRUCT_MESSAGE,
                 SSL_R_BAD_HANDSHAKE_STATE);
        return 0;

    case TLS_ST_CW_CHANGE:
        if (SSL_IS_DTLS(s))
            *confunc = dtls_construct_change_cipher_spec;
        else
            *confunc = tls_construct_change_cipher_spec;
        *mt = SSL3_MT_CHANGE_CIPHER_SPEC;
        break;

    case TLS_ST_CW_CLNT_HELLO:
        *confunc = tls_construct_client_hello;
        *mt = SSL3_MT_CLIENT_HELLO;
        break;

    case TLS_ST_CW_END_OF_EARLY_DATA:
        *confunc = tls_construct_end_of_early_data;
        *mt = SSL3_MT_END_OF_EARLY_DATA;
        break;

    case TLS_ST_PENDING_EARLY_DATA_END:
        *confunc = NULL;
        *mt = SSL3_MT_DUMMY;
        break;

    case TLS_ST_CW_CERT:
        *confunc = tls_construct_client_certificate;
        *mt = SSL3_MT_CERTIFICATE;
        break;

    case TLS_ST_CW_KEY_EXCH:
        *confunc = tls_construct_client_key_exchange;
        *mt = SSL3_MT_CLIENT_KEY_EXCHANGE;
        break;

    case TLS_ST_CW_CERT_VRFY:
        *confunc = tls_construct_cert_verify;
        *mt = SSL3_MT_CERTIFICATE_VERIFY;
        break;

#if !defined(OPENSSL_NO_NEXTPROTONEG)
    case TLS_ST_CW_NEXT_PROTO:
        *confunc = tls_construct_next_proto;
        *mt = SSL3_MT_NEXT_PROTO;
        break;
#endif
    case TLS_ST_CW_FINISHED:
        *confunc = tls_construct_finished;
        *mt = SSL3_MT_FINISHED;
        break;

    case TLS_ST_CW_KEY_UPDATE:
        *confunc = tls_construct_key_update;
        *mt = SSL3_MT_KEY_UPDATE;
        break;
    }

    return 1;
}