#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {size_t peer_finish_md_len; int /*<<< orphan*/  peer_finish_md; } ;
struct TYPE_18__ {size_t previous_client_finished_len; size_t previous_server_finished_len; TYPE_2__ tmp; int /*<<< orphan*/  previous_server_finished; int /*<<< orphan*/  previous_client_finished; scalar_t__ change_cipher_spec; } ;
struct TYPE_16__ {int cleanuphand; int /*<<< orphan*/  enc_read_state; } ;
struct TYPE_22__ {scalar_t__ post_handshake_auth; TYPE_6__* method; TYPE_4__* session; int /*<<< orphan*/  handshake_secret; int /*<<< orphan*/  master_secret; scalar_t__ server; TYPE_3__ s3; int /*<<< orphan*/  rlayer; TYPE_1__ statem; } ;
struct TYPE_21__ {TYPE_5__* ssl3_enc; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* change_cipher_state ) (TYPE_7__*,int) ;int /*<<< orphan*/  (* generate_master_secret ) (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_19__ {int /*<<< orphan*/  master_key_length; } ;
typedef  TYPE_7__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  MSG_PROCESS_RETURN ;

/* Variables and functions */
 scalar_t__ CRYPTO_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ENC_READ_STATE_VALID ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 size_t EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  MSG_PROCESS_ERROR ; 
 int /*<<< orphan*/  MSG_PROCESS_FINISHED_READING ; 
 int /*<<< orphan*/  PACKET_data (int /*<<< orphan*/ *) ; 
 size_t PACKET_remaining (int /*<<< orphan*/ *) ; 
 scalar_t__ RECORD_LAYER_processed_read_pending (int /*<<< orphan*/ *) ; 
 int SSL3_CC_APPLICATION ; 
 int SSL3_CHANGE_CIPHER_CLIENT_READ ; 
 int SSL3_CHANGE_CIPHER_SERVER_READ ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_DECRYPT_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_UNEXPECTED_MESSAGE ; 
 int /*<<< orphan*/  SSL_F_TLS_PROCESS_FINISHED ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_7__*) ; 
 scalar_t__ SSL_PHA_REQUESTED ; 
 int /*<<< orphan*/  SSL_R_BAD_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SSL_R_DIGEST_CHECK_FAILED ; 
 int /*<<< orphan*/  SSL_R_GOT_A_FIN_BEFORE_A_CCS ; 
 int /*<<< orphan*/  SSL_R_NOT_ON_RECORD_BOUNDARY ; 
 int /*<<< orphan*/  SSLfatal (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_7__*,int) ; 
 int /*<<< orphan*/  tls13_save_handshake_digest_for_pha (TYPE_7__*) ; 
 int /*<<< orphan*/  tls_process_initial_server_flight (TYPE_7__*) ; 

MSG_PROCESS_RETURN tls_process_finished(SSL *s, PACKET *pkt)
{
    size_t md_len;


    /* This is a real handshake so make sure we clean it up at the end */
    if (s->server) {
        /*
        * To get this far we must have read encrypted data from the client. We
        * no longer tolerate unencrypted alerts. This value is ignored if less
        * than TLSv1.3
        */
        s->statem.enc_read_state = ENC_READ_STATE_VALID;
        if (s->post_handshake_auth != SSL_PHA_REQUESTED)
            s->statem.cleanuphand = 1;
        if (SSL_IS_TLS13(s) && !tls13_save_handshake_digest_for_pha(s)) {
                /* SSLfatal() already called */
                return MSG_PROCESS_ERROR;
        }
    }

    /*
     * In TLSv1.3 a Finished message signals a key change so the end of the
     * message must be on a record boundary.
     */
    if (SSL_IS_TLS13(s) && RECORD_LAYER_processed_read_pending(&s->rlayer)) {
        SSLfatal(s, SSL_AD_UNEXPECTED_MESSAGE, SSL_F_TLS_PROCESS_FINISHED,
                 SSL_R_NOT_ON_RECORD_BOUNDARY);
        return MSG_PROCESS_ERROR;
    }

    /* If this occurs, we have missed a message */
    if (!SSL_IS_TLS13(s) && !s->s3.change_cipher_spec) {
        SSLfatal(s, SSL_AD_UNEXPECTED_MESSAGE, SSL_F_TLS_PROCESS_FINISHED,
                 SSL_R_GOT_A_FIN_BEFORE_A_CCS);
        return MSG_PROCESS_ERROR;
    }
    s->s3.change_cipher_spec = 0;

    md_len = s->s3.tmp.peer_finish_md_len;

    if (md_len != PACKET_remaining(pkt)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_FINISHED,
                 SSL_R_BAD_DIGEST_LENGTH);
        return MSG_PROCESS_ERROR;
    }

    if (CRYPTO_memcmp(PACKET_data(pkt), s->s3.tmp.peer_finish_md,
                      md_len) != 0) {
        SSLfatal(s, SSL_AD_DECRYPT_ERROR, SSL_F_TLS_PROCESS_FINISHED,
                 SSL_R_DIGEST_CHECK_FAILED);
        return MSG_PROCESS_ERROR;
    }

    /*
     * Copy the finished so we can use it for renegotiation checks
     */
    if (!ossl_assert(md_len <= EVP_MAX_MD_SIZE)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_FINISHED,
                 ERR_R_INTERNAL_ERROR);
        return MSG_PROCESS_ERROR;
    }
    if (s->server) {
        memcpy(s->s3.previous_client_finished, s->s3.tmp.peer_finish_md,
               md_len);
        s->s3.previous_client_finished_len = md_len;
    } else {
        memcpy(s->s3.previous_server_finished, s->s3.tmp.peer_finish_md,
               md_len);
        s->s3.previous_server_finished_len = md_len;
    }

    /*
     * In TLS1.3 we also have to change cipher state and do any final processing
     * of the initial server flight (if we are a client)
     */
    if (SSL_IS_TLS13(s)) {
        if (s->server) {
            if (s->post_handshake_auth != SSL_PHA_REQUESTED &&
                    !s->method->ssl3_enc->change_cipher_state(s,
                    SSL3_CC_APPLICATION | SSL3_CHANGE_CIPHER_SERVER_READ)) {
                /* SSLfatal() already called */
                return MSG_PROCESS_ERROR;
            }
        } else {
            if (!s->method->ssl3_enc->generate_master_secret(s,
                    s->master_secret, s->handshake_secret, 0,
                    &s->session->master_key_length)) {
                /* SSLfatal() already called */
                return MSG_PROCESS_ERROR;
            }
            if (!s->method->ssl3_enc->change_cipher_state(s,
                    SSL3_CC_APPLICATION | SSL3_CHANGE_CIPHER_CLIENT_READ)) {
                /* SSLfatal() already called */
                return MSG_PROCESS_ERROR;
            }
            if (!tls_process_initial_server_flight(s)) {
                /* SSLfatal() already called */
                return MSG_PROCESS_ERROR;
            }
        }
    }

    return MSG_PROCESS_FINISHED_READING;
}