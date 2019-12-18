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
 int DTLS1_MT_HELLO_VERIFY_REQUEST ; 
#define  DTLS_ST_SW_HELLO_VERIFY_REQUEST 142 
 int SSL3_MT_CERTIFICATE ; 
 int SSL3_MT_CERTIFICATE_REQUEST ; 
 int SSL3_MT_CERTIFICATE_STATUS ; 
 int SSL3_MT_CERTIFICATE_VERIFY ; 
 int SSL3_MT_CHANGE_CIPHER_SPEC ; 
 int SSL3_MT_DUMMY ; 
 int SSL3_MT_ENCRYPTED_EXTENSIONS ; 
 int SSL3_MT_FINISHED ; 
 int SSL3_MT_HELLO_REQUEST ; 
 int SSL3_MT_KEY_UPDATE ; 
 int SSL3_MT_NEWSESSION_TICKET ; 
 int SSL3_MT_SERVER_DONE ; 
 int SSL3_MT_SERVER_HELLO ; 
 int SSL3_MT_SERVER_KEY_EXCHANGE ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_OSSL_STATEM_SERVER_CONSTRUCT_MESSAGE ; 
 int /*<<< orphan*/  SSL_IS_DTLS (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_R_BAD_HANDSHAKE_STATE ; 
 int /*<<< orphan*/  SSLfatal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TLS_ST_EARLY_DATA 141 
#define  TLS_ST_SW_CERT 140 
#define  TLS_ST_SW_CERT_REQ 139 
#define  TLS_ST_SW_CERT_STATUS 138 
#define  TLS_ST_SW_CERT_VRFY 137 
#define  TLS_ST_SW_CHANGE 136 
#define  TLS_ST_SW_ENCRYPTED_EXTENSIONS 135 
#define  TLS_ST_SW_FINISHED 134 
#define  TLS_ST_SW_HELLO_REQ 133 
#define  TLS_ST_SW_KEY_EXCH 132 
#define  TLS_ST_SW_KEY_UPDATE 131 
#define  TLS_ST_SW_SESSION_TICKET 130 
#define  TLS_ST_SW_SRVR_DONE 129 
#define  TLS_ST_SW_SRVR_HELLO 128 
 int /*<<< orphan*/ * dtls_construct_change_cipher_spec ; 
 int /*<<< orphan*/ * dtls_construct_hello_verify_request ; 
 int /*<<< orphan*/ * tls_construct_cert_status ; 
 int /*<<< orphan*/ * tls_construct_cert_verify ; 
 int /*<<< orphan*/ * tls_construct_certificate_request ; 
 int /*<<< orphan*/ * tls_construct_change_cipher_spec ; 
 int /*<<< orphan*/ * tls_construct_encrypted_extensions ; 
 int /*<<< orphan*/ * tls_construct_finished ; 
 int /*<<< orphan*/ * tls_construct_key_update ; 
 int /*<<< orphan*/ * tls_construct_new_session_ticket ; 
 int /*<<< orphan*/ * tls_construct_server_certificate ; 
 int /*<<< orphan*/ * tls_construct_server_done ; 
 int /*<<< orphan*/ * tls_construct_server_hello ; 
 int /*<<< orphan*/ * tls_construct_server_key_exchange ; 

int ossl_statem_server_construct_message(SSL *s, WPACKET *pkt,
                                         confunc_f *confunc, int *mt)
{
    OSSL_STATEM *st = &s->statem;

    switch (st->hand_state) {
    default:
        /* Shouldn't happen */
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_OSSL_STATEM_SERVER_CONSTRUCT_MESSAGE,
                 SSL_R_BAD_HANDSHAKE_STATE);
        return 0;

    case TLS_ST_SW_CHANGE:
        if (SSL_IS_DTLS(s))
            *confunc = dtls_construct_change_cipher_spec;
        else
            *confunc = tls_construct_change_cipher_spec;
        *mt = SSL3_MT_CHANGE_CIPHER_SPEC;
        break;

    case DTLS_ST_SW_HELLO_VERIFY_REQUEST:
        *confunc = dtls_construct_hello_verify_request;
        *mt = DTLS1_MT_HELLO_VERIFY_REQUEST;
        break;

    case TLS_ST_SW_HELLO_REQ:
        /* No construction function needed */
        *confunc = NULL;
        *mt = SSL3_MT_HELLO_REQUEST;
        break;

    case TLS_ST_SW_SRVR_HELLO:
        *confunc = tls_construct_server_hello;
        *mt = SSL3_MT_SERVER_HELLO;
        break;

    case TLS_ST_SW_CERT:
        *confunc = tls_construct_server_certificate;
        *mt = SSL3_MT_CERTIFICATE;
        break;

    case TLS_ST_SW_CERT_VRFY:
        *confunc = tls_construct_cert_verify;
        *mt = SSL3_MT_CERTIFICATE_VERIFY;
        break;


    case TLS_ST_SW_KEY_EXCH:
        *confunc = tls_construct_server_key_exchange;
        *mt = SSL3_MT_SERVER_KEY_EXCHANGE;
        break;

    case TLS_ST_SW_CERT_REQ:
        *confunc = tls_construct_certificate_request;
        *mt = SSL3_MT_CERTIFICATE_REQUEST;
        break;

    case TLS_ST_SW_SRVR_DONE:
        *confunc = tls_construct_server_done;
        *mt = SSL3_MT_SERVER_DONE;
        break;

    case TLS_ST_SW_SESSION_TICKET:
        *confunc = tls_construct_new_session_ticket;
        *mt = SSL3_MT_NEWSESSION_TICKET;
        break;

    case TLS_ST_SW_CERT_STATUS:
        *confunc = tls_construct_cert_status;
        *mt = SSL3_MT_CERTIFICATE_STATUS;
        break;

    case TLS_ST_SW_FINISHED:
        *confunc = tls_construct_finished;
        *mt = SSL3_MT_FINISHED;
        break;

    case TLS_ST_EARLY_DATA:
        *confunc = NULL;
        *mt = SSL3_MT_DUMMY;
        break;

    case TLS_ST_SW_ENCRYPTED_EXTENSIONS:
        *confunc = tls_construct_encrypted_extensions;
        *mt = SSL3_MT_ENCRYPTED_EXTENSIONS;
        break;

    case TLS_ST_SW_KEY_UPDATE:
        *confunc = tls_construct_key_update;
        *mt = SSL3_MT_KEY_UPDATE;
        break;
    }

    return 1;
}