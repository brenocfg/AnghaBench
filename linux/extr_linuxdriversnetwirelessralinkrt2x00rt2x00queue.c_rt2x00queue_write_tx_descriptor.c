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
struct txentry_desc {int dummy; } ;
struct queue_entry {struct data_queue* queue; } ;
struct data_queue {TYPE_3__* rt2x00dev; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {TYPE_1__* lib; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* write_tx_desc ) (struct queue_entry*,struct txentry_desc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_FRAME_TX ; 
 int /*<<< orphan*/  rt2x00debug_dump_frame (TYPE_3__*,int /*<<< orphan*/ ,struct queue_entry*) ; 
 int /*<<< orphan*/  stub1 (struct queue_entry*,struct txentry_desc*) ; 

__attribute__((used)) static void rt2x00queue_write_tx_descriptor(struct queue_entry *entry,
					    struct txentry_desc *txdesc)
{
	struct data_queue *queue = entry->queue;

	queue->rt2x00dev->ops->lib->write_tx_desc(entry, txdesc);

	/*
	 * All processing on the frame has been completed, this means
	 * it is now ready to be dumped to userspace through debugfs.
	 */
	rt2x00debug_dump_frame(queue->rt2x00dev, DUMP_FRAME_TX, entry);
}