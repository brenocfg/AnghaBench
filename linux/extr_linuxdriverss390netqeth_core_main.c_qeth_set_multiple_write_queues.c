#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int no_out_queues; int default_out_queue; int /*<<< orphan*/  state; } ;
struct qeth_card {TYPE_1__ qdio; } ;

/* Variables and functions */
 scalar_t__ QETH_QDIO_UNINITIALIZED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_free_qdio_buffers (struct qeth_card*) ; 

__attribute__((used)) static void qeth_set_multiple_write_queues(struct qeth_card *card)
{
	if ((atomic_read(&card->qdio.state) != QETH_QDIO_UNINITIALIZED) &&
	    (card->qdio.no_out_queues == 1)) {
		qeth_free_qdio_buffers(card);
		card->qdio.default_out_queue = 2;
	}
	card->qdio.no_out_queues = 4;
}