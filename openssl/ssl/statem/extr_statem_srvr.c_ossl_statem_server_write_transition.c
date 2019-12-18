#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WRITE_TRAN ;
struct TYPE_24__ {int hand_state; int request_state; } ;
struct TYPE_22__ {int /*<<< orphan*/  ticket_expected; int /*<<< orphan*/  status_expected; } ;
struct TYPE_20__ {TYPE_2__* new_cipher; } ;
struct TYPE_21__ {TYPE_3__ tmp; } ;
struct TYPE_23__ {int /*<<< orphan*/  hit; TYPE_5__ ext; TYPE_4__ s3; int /*<<< orphan*/  renegotiate; TYPE_1__* d1; TYPE_7__ statem; } ;
struct TYPE_19__ {int algorithm_auth; } ;
struct TYPE_18__ {int /*<<< orphan*/  cookie_verified; } ;
typedef  TYPE_6__ SSL ;
typedef  TYPE_7__ OSSL_STATEM ;

/* Variables and functions */
#define  DTLS_ST_SW_HELLO_VERIFY_REQUEST 142 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_OSSL_STATEM_SERVER_WRITE_TRANSITION ; 
 int /*<<< orphan*/  SSL_IS_DTLS (TYPE_6__*) ; 
 int /*<<< orphan*/  SSL_IS_FIRST_HANDSHAKE (TYPE_6__*) ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_6__*) ; 
 int SSL_OP_COOKIE_EXCHANGE ; 
 int SSL_aNULL ; 
 int SSL_aPSK ; 
 int SSL_aSRP ; 
 int SSL_get_options (TYPE_6__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TLS_ST_BEFORE 141 
#define  TLS_ST_OK 140 
#define  TLS_ST_SR_CLNT_HELLO 139 
#define  TLS_ST_SR_FINISHED 138 
#define  TLS_ST_SW_CERT 137 
#define  TLS_ST_SW_CERT_REQ 136 
#define  TLS_ST_SW_CERT_STATUS 135 
#define  TLS_ST_SW_CHANGE 134 
#define  TLS_ST_SW_FINISHED 133 
#define  TLS_ST_SW_HELLO_REQ 132 
#define  TLS_ST_SW_KEY_EXCH 131 
#define  TLS_ST_SW_SESSION_TICKET 130 
#define  TLS_ST_SW_SRVR_DONE 129 
#define  TLS_ST_SW_SRVR_HELLO 128 
 int /*<<< orphan*/  WRITE_TRAN_CONTINUE ; 
 int /*<<< orphan*/  WRITE_TRAN_ERROR ; 
 int /*<<< orphan*/  WRITE_TRAN_FINISHED ; 
 int /*<<< orphan*/  ossl_statem_server13_write_transition (TYPE_6__*) ; 
 int /*<<< orphan*/  send_certificate_request (TYPE_6__*) ; 
 int /*<<< orphan*/  send_server_key_exchange (TYPE_6__*) ; 
 int /*<<< orphan*/  tls_setup_handshake (TYPE_6__*) ; 

WRITE_TRAN ossl_statem_server_write_transition(SSL *s)
{
    OSSL_STATEM *st = &s->statem;

    /*
     * Note that before the ClientHello we don't know what version we are going
     * to negotiate yet, so we don't take this branch until later
     */

    if (SSL_IS_TLS13(s))
        return ossl_statem_server13_write_transition(s);

    switch (st->hand_state) {
    default:
        /* Shouldn't happen */
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_OSSL_STATEM_SERVER_WRITE_TRANSITION,
                 ERR_R_INTERNAL_ERROR);
        return WRITE_TRAN_ERROR;

    case TLS_ST_OK:
        if (st->request_state == TLS_ST_SW_HELLO_REQ) {
            /* We must be trying to renegotiate */
            st->hand_state = TLS_ST_SW_HELLO_REQ;
            st->request_state = TLS_ST_BEFORE;
            return WRITE_TRAN_CONTINUE;
        }
        /* Must be an incoming ClientHello */
        if (!tls_setup_handshake(s)) {
            /* SSLfatal() already called */
            return WRITE_TRAN_ERROR;
        }
        /* Fall through */

    case TLS_ST_BEFORE:
        /* Just go straight to trying to read from the client */
        return WRITE_TRAN_FINISHED;

    case TLS_ST_SW_HELLO_REQ:
        st->hand_state = TLS_ST_OK;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_SR_CLNT_HELLO:
        if (SSL_IS_DTLS(s) && !s->d1->cookie_verified
            && (SSL_get_options(s) & SSL_OP_COOKIE_EXCHANGE)) {
            st->hand_state = DTLS_ST_SW_HELLO_VERIFY_REQUEST;
        } else if (s->renegotiate == 0 && !SSL_IS_FIRST_HANDSHAKE(s)) {
            /* We must have rejected the renegotiation */
            st->hand_state = TLS_ST_OK;
            return WRITE_TRAN_CONTINUE;
        } else {
            st->hand_state = TLS_ST_SW_SRVR_HELLO;
        }
        return WRITE_TRAN_CONTINUE;

    case DTLS_ST_SW_HELLO_VERIFY_REQUEST:
        return WRITE_TRAN_FINISHED;

    case TLS_ST_SW_SRVR_HELLO:
        if (s->hit) {
            if (s->ext.ticket_expected)
                st->hand_state = TLS_ST_SW_SESSION_TICKET;
            else
                st->hand_state = TLS_ST_SW_CHANGE;
        } else {
            /* Check if it is anon DH or anon ECDH, */
            /* normal PSK or SRP */
            if (!(s->s3.tmp.new_cipher->algorithm_auth &
                  (SSL_aNULL | SSL_aSRP | SSL_aPSK))) {
                st->hand_state = TLS_ST_SW_CERT;
            } else if (send_server_key_exchange(s)) {
                st->hand_state = TLS_ST_SW_KEY_EXCH;
            } else if (send_certificate_request(s)) {
                st->hand_state = TLS_ST_SW_CERT_REQ;
            } else {
                st->hand_state = TLS_ST_SW_SRVR_DONE;
            }
        }
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_SW_CERT:
        if (s->ext.status_expected) {
            st->hand_state = TLS_ST_SW_CERT_STATUS;
            return WRITE_TRAN_CONTINUE;
        }
        /* Fall through */

    case TLS_ST_SW_CERT_STATUS:
        if (send_server_key_exchange(s)) {
            st->hand_state = TLS_ST_SW_KEY_EXCH;
            return WRITE_TRAN_CONTINUE;
        }
        /* Fall through */

    case TLS_ST_SW_KEY_EXCH:
        if (send_certificate_request(s)) {
            st->hand_state = TLS_ST_SW_CERT_REQ;
            return WRITE_TRAN_CONTINUE;
        }
        /* Fall through */

    case TLS_ST_SW_CERT_REQ:
        st->hand_state = TLS_ST_SW_SRVR_DONE;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_SW_SRVR_DONE:
        return WRITE_TRAN_FINISHED;

    case TLS_ST_SR_FINISHED:
        if (s->hit) {
            st->hand_state = TLS_ST_OK;
            return WRITE_TRAN_CONTINUE;
        } else if (s->ext.ticket_expected) {
            st->hand_state = TLS_ST_SW_SESSION_TICKET;
        } else {
            st->hand_state = TLS_ST_SW_CHANGE;
        }
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_SW_SESSION_TICKET:
        st->hand_state = TLS_ST_SW_CHANGE;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_SW_CHANGE:
        st->hand_state = TLS_ST_SW_FINISHED;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_SW_FINISHED:
        if (s->hit) {
            return WRITE_TRAN_FINISHED;
        }
        st->hand_state = TLS_ST_OK;
        return WRITE_TRAN_CONTINUE;
    }
}