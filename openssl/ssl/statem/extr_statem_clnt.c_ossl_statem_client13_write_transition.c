#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WRITE_TRAN ;
struct TYPE_12__ {int hand_state; } ;
struct TYPE_9__ {int cert_req; } ;
struct TYPE_10__ {TYPE_2__ tmp; } ;
struct TYPE_8__ {int /*<<< orphan*/  early_data; } ;
struct TYPE_11__ {int shutdown; int options; int /*<<< orphan*/  key_update; TYPE_3__ s3; TYPE_1__ ext; int /*<<< orphan*/  hello_retry_request; int /*<<< orphan*/  early_data_state; int /*<<< orphan*/  post_handshake_auth; TYPE_5__ statem; } ;
typedef  TYPE_4__ SSL ;
typedef  TYPE_5__ OSSL_STATEM ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_EARLY_DATA_ACCEPTED ; 
 int /*<<< orphan*/  SSL_EARLY_DATA_FINISHED_WRITING ; 
 int /*<<< orphan*/  SSL_EARLY_DATA_WRITE_RETRY ; 
 int /*<<< orphan*/  SSL_F_OSSL_STATEM_CLIENT13_WRITE_TRANSITION ; 
 int /*<<< orphan*/  SSL_HRR_NONE ; 
 int /*<<< orphan*/  SSL_KEY_UPDATE_NONE ; 
 int SSL_OP_ENABLE_MIDDLEBOX_COMPAT ; 
 int /*<<< orphan*/  SSL_PHA_REQUESTED ; 
 int SSL_SENT_SHUTDOWN ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TLS_ST_CR_CERT_REQ 139 
#define  TLS_ST_CR_FINISHED 138 
#define  TLS_ST_CR_KEY_UPDATE 137 
#define  TLS_ST_CR_SESSION_TICKET 136 
#define  TLS_ST_CW_CERT 135 
#define  TLS_ST_CW_CERT_VRFY 134 
#define  TLS_ST_CW_CHANGE 133 
#define  TLS_ST_CW_END_OF_EARLY_DATA 132 
#define  TLS_ST_CW_FINISHED 131 
#define  TLS_ST_CW_KEY_UPDATE 130 
#define  TLS_ST_OK 129 
#define  TLS_ST_PENDING_EARLY_DATA_END 128 
 int /*<<< orphan*/  WRITE_TRAN_CONTINUE ; 
 int /*<<< orphan*/  WRITE_TRAN_ERROR ; 
 int /*<<< orphan*/  WRITE_TRAN_FINISHED ; 
 int /*<<< orphan*/  ossl_assert (int) ; 

__attribute__((used)) static WRITE_TRAN ossl_statem_client13_write_transition(SSL *s)
{
    OSSL_STATEM *st = &s->statem;

    /*
     * Note: There are no cases for TLS_ST_BEFORE because we haven't negotiated
     * TLSv1.3 yet at that point. They are handled by
     * ossl_statem_client_write_transition().
     */
    switch (st->hand_state) {
    default:
        /* Shouldn't happen */
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_OSSL_STATEM_CLIENT13_WRITE_TRANSITION,
                 ERR_R_INTERNAL_ERROR);
        return WRITE_TRAN_ERROR;

    case TLS_ST_CR_CERT_REQ:
        if (s->post_handshake_auth == SSL_PHA_REQUESTED) {
            st->hand_state = TLS_ST_CW_CERT;
            return WRITE_TRAN_CONTINUE;
        }
        /*
         * We should only get here if we received a CertificateRequest after
         * we already sent close_notify
         */
        if (!ossl_assert((s->shutdown & SSL_SENT_SHUTDOWN) != 0)) {
            /* Shouldn't happen - same as default case */
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_OSSL_STATEM_CLIENT13_WRITE_TRANSITION,
                     ERR_R_INTERNAL_ERROR);
            return WRITE_TRAN_ERROR;
        }
        st->hand_state = TLS_ST_OK;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_CR_FINISHED:
        if (s->early_data_state == SSL_EARLY_DATA_WRITE_RETRY
                || s->early_data_state == SSL_EARLY_DATA_FINISHED_WRITING)
            st->hand_state = TLS_ST_PENDING_EARLY_DATA_END;
        else if ((s->options & SSL_OP_ENABLE_MIDDLEBOX_COMPAT) != 0
                 && s->hello_retry_request == SSL_HRR_NONE)
            st->hand_state = TLS_ST_CW_CHANGE;
        else
            st->hand_state = (s->s3.tmp.cert_req != 0) ? TLS_ST_CW_CERT
                                                        : TLS_ST_CW_FINISHED;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_PENDING_EARLY_DATA_END:
        if (s->ext.early_data == SSL_EARLY_DATA_ACCEPTED) {
            st->hand_state = TLS_ST_CW_END_OF_EARLY_DATA;
            return WRITE_TRAN_CONTINUE;
        }
        /* Fall through */

    case TLS_ST_CW_END_OF_EARLY_DATA:
    case TLS_ST_CW_CHANGE:
        st->hand_state = (s->s3.tmp.cert_req != 0) ? TLS_ST_CW_CERT
                                                    : TLS_ST_CW_FINISHED;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_CW_CERT:
        /* If a non-empty Certificate we also send CertificateVerify */
        st->hand_state = (s->s3.tmp.cert_req == 1) ? TLS_ST_CW_CERT_VRFY
                                                    : TLS_ST_CW_FINISHED;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_CW_CERT_VRFY:
        st->hand_state = TLS_ST_CW_FINISHED;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_CR_KEY_UPDATE:
    case TLS_ST_CW_KEY_UPDATE:
    case TLS_ST_CR_SESSION_TICKET:
    case TLS_ST_CW_FINISHED:
        st->hand_state = TLS_ST_OK;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_OK:
        if (s->key_update != SSL_KEY_UPDATE_NONE) {
            st->hand_state = TLS_ST_CW_KEY_UPDATE;
            return WRITE_TRAN_CONTINUE;
        }

        /* Try to read from the server instead */
        return WRITE_TRAN_FINISHED;
    }
}