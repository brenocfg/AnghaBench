#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int hand_state; } ;
struct TYPE_9__ {int /*<<< orphan*/  cert_request; } ;
struct TYPE_10__ {TYPE_2__ tmp; } ;
struct TYPE_8__ {int /*<<< orphan*/  early_data; } ;
struct TYPE_12__ {int /*<<< orphan*/  post_handshake_auth; int /*<<< orphan*/  early_data_state; TYPE_4__* session; TYPE_3__ s3; TYPE_1__ ext; int /*<<< orphan*/  hello_retry_request; TYPE_6__ statem; } ;
struct TYPE_11__ {int /*<<< orphan*/ * peer; } ;
typedef  TYPE_5__ SSL ;
typedef  TYPE_6__ OSSL_STATEM ;

/* Variables and functions */
 int SSL3_MT_CERTIFICATE ; 
 int SSL3_MT_CERTIFICATE_VERIFY ; 
 int SSL3_MT_CLIENT_HELLO ; 
 int SSL3_MT_END_OF_EARLY_DATA ; 
 int SSL3_MT_FINISHED ; 
 int SSL3_MT_KEY_UPDATE ; 
 int /*<<< orphan*/  SSL_EARLY_DATA_ACCEPTED ; 
 int /*<<< orphan*/  SSL_EARLY_DATA_READING ; 
 int /*<<< orphan*/  SSL_HRR_PENDING ; 
 int /*<<< orphan*/  SSL_PHA_REQUESTED ; 
#define  TLS_ST_EARLY_DATA 133 
#define  TLS_ST_OK 132 
#define  TLS_ST_SR_CERT 131 
#define  TLS_ST_SR_CERT_VRFY 130 
 int TLS_ST_SR_CLNT_HELLO ; 
#define  TLS_ST_SR_END_OF_EARLY_DATA 129 
 void* TLS_ST_SR_FINISHED ; 
 int TLS_ST_SR_KEY_UPDATE ; 
#define  TLS_ST_SW_FINISHED 128 

__attribute__((used)) static int ossl_statem_server13_read_transition(SSL *s, int mt)
{
    OSSL_STATEM *st = &s->statem;

    /*
     * Note: There is no case for TLS_ST_BEFORE because at that stage we have
     * not negotiated TLSv1.3 yet, so that case is handled by
     * ossl_statem_server_read_transition()
     */
    switch (st->hand_state) {
    default:
        break;

    case TLS_ST_EARLY_DATA:
        if (s->hello_retry_request == SSL_HRR_PENDING) {
            if (mt == SSL3_MT_CLIENT_HELLO) {
                st->hand_state = TLS_ST_SR_CLNT_HELLO;
                return 1;
            }
            break;
        } else if (s->ext.early_data == SSL_EARLY_DATA_ACCEPTED) {
            if (mt == SSL3_MT_END_OF_EARLY_DATA) {
                st->hand_state = TLS_ST_SR_END_OF_EARLY_DATA;
                return 1;
            }
            break;
        }
        /* Fall through */

    case TLS_ST_SR_END_OF_EARLY_DATA:
    case TLS_ST_SW_FINISHED:
        if (s->s3.tmp.cert_request) {
            if (mt == SSL3_MT_CERTIFICATE) {
                st->hand_state = TLS_ST_SR_CERT;
                return 1;
            }
        } else {
            if (mt == SSL3_MT_FINISHED) {
                st->hand_state = TLS_ST_SR_FINISHED;
                return 1;
            }
        }
        break;

    case TLS_ST_SR_CERT:
        if (s->session->peer == NULL) {
            if (mt == SSL3_MT_FINISHED) {
                st->hand_state = TLS_ST_SR_FINISHED;
                return 1;
            }
        } else {
            if (mt == SSL3_MT_CERTIFICATE_VERIFY) {
                st->hand_state = TLS_ST_SR_CERT_VRFY;
                return 1;
            }
        }
        break;

    case TLS_ST_SR_CERT_VRFY:
        if (mt == SSL3_MT_FINISHED) {
            st->hand_state = TLS_ST_SR_FINISHED;
            return 1;
        }
        break;

    case TLS_ST_OK:
        /*
         * Its never ok to start processing handshake messages in the middle of
         * early data (i.e. before we've received the end of early data alert)
         */
        if (s->early_data_state == SSL_EARLY_DATA_READING)
            break;

        if (mt == SSL3_MT_CERTIFICATE
                && s->post_handshake_auth == SSL_PHA_REQUESTED) {
            st->hand_state = TLS_ST_SR_CERT;
            return 1;
        }

        if (mt == SSL3_MT_KEY_UPDATE) {
            st->hand_state = TLS_ST_SR_KEY_UPDATE;
            return 1;
        }
        break;
    }

    /* No valid transition found */
    return 0;
}