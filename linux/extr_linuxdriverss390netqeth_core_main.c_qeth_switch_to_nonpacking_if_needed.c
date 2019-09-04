#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qeth_qdio_out_q {scalar_t__ do_pack; TYPE_3__* card; int /*<<< orphan*/  used_buffers; } ;
struct TYPE_5__ {int /*<<< orphan*/  sc_p_dp; } ;
struct TYPE_4__ {scalar_t__ performance_stats; } ;
struct TYPE_6__ {TYPE_2__ perf_stats; TYPE_1__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_TEXT (TYPE_3__*,int,char*) ; 
 scalar_t__ QETH_LOW_WATERMARK_PACK ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int qeth_prep_flush_pack_buffer (struct qeth_qdio_out_q*) ; 

__attribute__((used)) static int qeth_switch_to_nonpacking_if_needed(struct qeth_qdio_out_q *queue)
{
	if (queue->do_pack) {
		if (atomic_read(&queue->used_buffers)
		    <= QETH_LOW_WATERMARK_PACK) {
			/* switch PACKING -> non-PACKING */
			QETH_CARD_TEXT(queue->card, 6, "pack->np");
			if (queue->card->options.performance_stats)
				queue->card->perf_stats.sc_p_dp++;
			queue->do_pack = 0;
			return qeth_prep_flush_pack_buffer(queue);
		}
	}
	return 0;
}