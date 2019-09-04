#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int no_out_queues; scalar_t__ default_out_queue; int /*<<< orphan*/  state; } ;
struct qeth_card {TYPE_2__ qdio; TYPE_1__* gdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ QETH_QDIO_UNINITIALIZED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  qeth_free_qdio_buffers (struct qeth_card*) ; 

__attribute__((used)) static void qeth_set_single_write_queues(struct qeth_card *card)
{
	if ((atomic_read(&card->qdio.state) != QETH_QDIO_UNINITIALIZED) &&
	    (card->qdio.no_out_queues == 4))
		qeth_free_qdio_buffers(card);

	card->qdio.no_out_queues = 1;
	if (card->qdio.default_out_queue != 0)
		dev_info(&card->gdev->dev, "Priority Queueing not supported\n");

	card->qdio.default_out_queue = 0;
}