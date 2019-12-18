#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_16__ ;
typedef  struct TYPE_20__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pitem ;
struct TYPE_21__ {TYPE_2__* d; int /*<<< orphan*/  rrec; } ;
struct TYPE_25__ {TYPE_16__ rlayer; } ;
struct TYPE_24__ {scalar_t__ length; } ;
struct TYPE_22__ {scalar_t__ epoch; int /*<<< orphan*/  q; } ;
struct TYPE_20__ {scalar_t__ epoch; } ;
struct TYPE_23__ {scalar_t__ r_epoch; TYPE_1__ unprocessed_rcds; TYPE_13__ processed_rcds; } ;
typedef  TYPE_3__ SSL3_RECORD ;
typedef  int /*<<< orphan*/  SSL3_BUFFER ;
typedef  TYPE_4__ SSL ;
typedef  int /*<<< orphan*/  DTLS1_BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_dgram_is_sctp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/ * RECORD_LAYER_get_rbuf (TYPE_16__*) ; 
 TYPE_3__* RECORD_LAYER_get_rrec (TYPE_16__*) ; 
 int /*<<< orphan*/  RECORD_LAYER_reset_packet_length (TYPE_16__*) ; 
 scalar_t__ SSL3_BUFFER_get_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL3_RECORD_get_seq_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_DTLS1_PROCESS_BUFFERED_RECORDS ; 
 int /*<<< orphan*/  SSL_get_rbio (TYPE_4__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dtls1_buffer_record (TYPE_4__*,TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dtls1_get_bitmap (TYPE_4__*,TYPE_3__*,unsigned int*) ; 
 int /*<<< orphan*/  dtls1_get_unprocessed_record (TYPE_4__*) ; 
 int /*<<< orphan*/  dtls1_process_record (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int dtls1_record_replay_check (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ossl_statem_in_error (TYPE_4__*) ; 
 int /*<<< orphan*/ * pqueue_peek (int /*<<< orphan*/ ) ; 

int dtls1_process_buffered_records(SSL *s)
{
    pitem *item;
    SSL3_BUFFER *rb;
    SSL3_RECORD *rr;
    DTLS1_BITMAP *bitmap;
    unsigned int is_next_epoch;
    int replayok = 1;

    item = pqueue_peek(s->rlayer.d->unprocessed_rcds.q);
    if (item) {
        /* Check if epoch is current. */
        if (s->rlayer.d->unprocessed_rcds.epoch != s->rlayer.d->r_epoch)
            return 1;         /* Nothing to do. */

        rr = RECORD_LAYER_get_rrec(&s->rlayer);

        rb = RECORD_LAYER_get_rbuf(&s->rlayer);

        if (SSL3_BUFFER_get_left(rb) > 0) {
            /*
             * We've still got data from the current packet to read. There could
             * be a record from the new epoch in it - so don't overwrite it
             * with the unprocessed records yet (we'll do it when we've
             * finished reading the current packet).
             */
            return 1;
        }

        /* Process all the records. */
        while (pqueue_peek(s->rlayer.d->unprocessed_rcds.q)) {
            dtls1_get_unprocessed_record(s);
            bitmap = dtls1_get_bitmap(s, rr, &is_next_epoch);
            if (bitmap == NULL) {
                /*
                 * Should not happen. This will only ever be NULL when the
                 * current record is from a different epoch. But that cannot
                 * be the case because we already checked the epoch above
                 */
                 SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                          SSL_F_DTLS1_PROCESS_BUFFERED_RECORDS,
                          ERR_R_INTERNAL_ERROR);
                 return 0;
            }
#ifndef OPENSSL_NO_SCTP
            /* Only do replay check if no SCTP bio */
            if (!BIO_dgram_is_sctp(SSL_get_rbio(s)))
#endif
            {
                /*
                 * Check whether this is a repeat, or aged record. We did this
                 * check once already when we first received the record - but
                 * we might have updated the window since then due to
                 * records we subsequently processed.
                 */
                replayok = dtls1_record_replay_check(s, bitmap);
            }

            if (!replayok || !dtls1_process_record(s, bitmap)) {
                if (ossl_statem_in_error(s)) {
                    /* dtls1_process_record called SSLfatal() */
                    return -1;
                }
                /* dump this record */
                rr->length = 0;
                RECORD_LAYER_reset_packet_length(&s->rlayer);
                continue;
            }

            if (dtls1_buffer_record(s, &(s->rlayer.d->processed_rcds),
                    SSL3_RECORD_get_seq_num(s->rlayer.rrec)) < 0) {
                /* SSLfatal() already called */
                return 0;
            }
        }
    }

    /*
     * sync epoch numbers once all the unprocessed records have been
     * processed
     */
    s->rlayer.d->processed_rcds.epoch = s->rlayer.d->r_epoch;
    s->rlayer.d->unprocessed_rcds.epoch = s->rlayer.d->r_epoch + 1;

    return 1;
}