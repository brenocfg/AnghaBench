#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ early_data_state; TYPE_2__* method; int /*<<< orphan*/  rlayer; } ;
struct TYPE_8__ {TYPE_1__* ssl3_enc; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* change_cipher_state ) (TYPE_3__*,int) ;} ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  MSG_PROCESS_RETURN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  MSG_PROCESS_CONTINUE_READING ; 
 int /*<<< orphan*/  MSG_PROCESS_ERROR ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 scalar_t__ RECORD_LAYER_processed_read_pending (int /*<<< orphan*/ *) ; 
 int SSL3_CC_HANDSHAKE ; 
 int SSL3_CHANGE_CIPHER_SERVER_READ ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_UNEXPECTED_MESSAGE ; 
 scalar_t__ SSL_EARLY_DATA_FINISHED_READING ; 
 scalar_t__ SSL_EARLY_DATA_READING ; 
 scalar_t__ SSL_EARLY_DATA_READ_RETRY ; 
 int /*<<< orphan*/  SSL_F_TLS_PROCESS_END_OF_EARLY_DATA ; 
 int /*<<< orphan*/  SSL_R_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SSL_R_NOT_ON_RECORD_BOUNDARY ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int) ; 

MSG_PROCESS_RETURN tls_process_end_of_early_data(SSL *s, PACKET *pkt)
{
    if (PACKET_remaining(pkt) != 0) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_END_OF_EARLY_DATA,
                 SSL_R_LENGTH_MISMATCH);
        return MSG_PROCESS_ERROR;
    }

    if (s->early_data_state != SSL_EARLY_DATA_READING
            && s->early_data_state != SSL_EARLY_DATA_READ_RETRY) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_END_OF_EARLY_DATA,
                 ERR_R_INTERNAL_ERROR);
        return MSG_PROCESS_ERROR;
    }

    /*
     * EndOfEarlyData signals a key change so the end of the message must be on
     * a record boundary.
     */
    if (RECORD_LAYER_processed_read_pending(&s->rlayer)) {
        SSLfatal(s, SSL_AD_UNEXPECTED_MESSAGE,
                 SSL_F_TLS_PROCESS_END_OF_EARLY_DATA,
                 SSL_R_NOT_ON_RECORD_BOUNDARY);
        return MSG_PROCESS_ERROR;
    }

    s->early_data_state = SSL_EARLY_DATA_FINISHED_READING;
    if (!s->method->ssl3_enc->change_cipher_state(s,
                SSL3_CC_HANDSHAKE | SSL3_CHANGE_CIPHER_SERVER_READ)) {
        /* SSLfatal() already called */
        return MSG_PROCESS_ERROR;
    }

    return MSG_PROCESS_CONTINUE_READING;
}