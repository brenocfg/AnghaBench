#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct qeth_qdio_out_q {TYPE_8__* card; int /*<<< orphan*/  used_buffers; TYPE_2__* bufstates; struct qeth_qdio_out_buffer** bufs; } ;
struct qeth_qdio_out_buffer {TYPE_7__* buffer; int /*<<< orphan*/  state; } ;
struct TYPE_14__ {scalar_t__ outbound_handler_start_time; int /*<<< orphan*/  outbound_handler_time; int /*<<< orphan*/  outbound_handler_cnt; } ;
struct TYPE_13__ {scalar_t__ cq; scalar_t__ performance_stats; } ;
struct TYPE_12__ {scalar_t__ type; } ;
struct TYPE_9__ {struct qeth_qdio_out_q** out_qs; } ;
struct qeth_card {TYPE_6__ perf_stats; TYPE_5__ options; TYPE_4__ info; int /*<<< orphan*/  dev; TYPE_1__ qdio; } ;
struct ccw_device {int dummy; } ;
typedef  enum iucv_tx_notify { ____Placeholder_iucv_tx_notify } iucv_tx_notify ;
struct TYPE_16__ {int /*<<< orphan*/  dev; } ;
struct TYPE_15__ {TYPE_3__* element; } ;
struct TYPE_11__ {int /*<<< orphan*/  sflags; } ;
struct TYPE_10__ {int flags; } ;

/* Variables and functions */
 unsigned int QDIO_ERROR_FATAL ; 
 int QDIO_MAX_BUFFERS_PER_Q ; 
 int QDIO_OUTBUF_STATE_FLAG_PENDING ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (TYPE_8__*,int,char*,int) ; 
 scalar_t__ QETH_CARD_TYPE_IQD ; 
 scalar_t__ QETH_CQ_ENABLED ; 
 int /*<<< orphan*/  QETH_MAX_BUFFER_ELEMENTS (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_QDIO_BUF_PENDING ; 
 scalar_t__ QETH_QDIO_BUF_PRIMED ; 
 int TX_NOTIFY_PENDING ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_check_outbound_queue (struct qeth_qdio_out_q*) ; 
 int /*<<< orphan*/  qeth_cleanup_handled_pending (struct qeth_qdio_out_q*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_clear_output_buffer (struct qeth_qdio_out_q*,struct qeth_qdio_out_buffer*) ; 
 int qeth_compute_cq_notification (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qeth_get_micros () ; 
 int /*<<< orphan*/  qeth_handle_send_error (struct qeth_card*,struct qeth_qdio_out_buffer*,unsigned int) ; 
 scalar_t__ qeth_init_qdio_out_buf (struct qeth_qdio_out_q*,int) ; 
 int /*<<< orphan*/  qeth_notify_skbs (struct qeth_qdio_out_q*,struct qeth_qdio_out_buffer*,int) ; 
 int /*<<< orphan*/  qeth_schedule_recovery (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_scrub_qdio_buffer (TYPE_7__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qeth_qdio_output_handler(struct ccw_device *ccwdev,
				     unsigned int qdio_error, int __queue,
				     int first_element, int count,
				     unsigned long card_ptr)
{
	struct qeth_card *card        = (struct qeth_card *) card_ptr;
	struct qeth_qdio_out_q *queue = card->qdio.out_qs[__queue];
	struct qeth_qdio_out_buffer *buffer;
	int i;

	QETH_CARD_TEXT(card, 6, "qdouhdl");
	if (qdio_error & QDIO_ERROR_FATAL) {
		QETH_CARD_TEXT(card, 2, "achkcond");
		netif_stop_queue(card->dev);
		qeth_schedule_recovery(card);
		return;
	}
	if (card->options.performance_stats) {
		card->perf_stats.outbound_handler_cnt++;
		card->perf_stats.outbound_handler_start_time =
			qeth_get_micros();
	}
	for (i = first_element; i < (first_element + count); ++i) {
		int bidx = i % QDIO_MAX_BUFFERS_PER_Q;
		buffer = queue->bufs[bidx];
		qeth_handle_send_error(card, buffer, qdio_error);

		if (queue->bufstates &&
		    (queue->bufstates[bidx].flags &
		     QDIO_OUTBUF_STATE_FLAG_PENDING) != 0) {
			WARN_ON_ONCE(card->options.cq != QETH_CQ_ENABLED);

			if (atomic_cmpxchg(&buffer->state,
					   QETH_QDIO_BUF_PRIMED,
					   QETH_QDIO_BUF_PENDING) ==
				QETH_QDIO_BUF_PRIMED) {
				qeth_notify_skbs(queue, buffer,
						 TX_NOTIFY_PENDING);
			}
			QETH_CARD_TEXT_(queue->card, 5, "pel%d", bidx);

			/* prepare the queue slot for re-use: */
			qeth_scrub_qdio_buffer(buffer->buffer,
					       QETH_MAX_BUFFER_ELEMENTS(card));
			if (qeth_init_qdio_out_buf(queue, bidx)) {
				QETH_CARD_TEXT(card, 2, "outofbuf");
				qeth_schedule_recovery(card);
			}
		} else {
			if (card->options.cq == QETH_CQ_ENABLED) {
				enum iucv_tx_notify n;

				n = qeth_compute_cq_notification(
					buffer->buffer->element[15].sflags, 0);
				qeth_notify_skbs(queue, buffer, n);
			}

			qeth_clear_output_buffer(queue, buffer);
		}
		qeth_cleanup_handled_pending(queue, bidx, 0);
	}
	atomic_sub(count, &queue->used_buffers);
	/* check if we need to do something on this outbound queue */
	if (card->info.type != QETH_CARD_TYPE_IQD)
		qeth_check_outbound_queue(queue);

	netif_wake_queue(queue->card->dev);
	if (card->options.performance_stats)
		card->perf_stats.outbound_handler_time += qeth_get_micros() -
			card->perf_stats.outbound_handler_start_time;
}