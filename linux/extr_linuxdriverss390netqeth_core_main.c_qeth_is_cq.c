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
struct TYPE_4__ {int no_in_queues; int /*<<< orphan*/ * c_q; } ;
struct TYPE_3__ {scalar_t__ cq; } ;
struct qeth_card {TYPE_2__ qdio; TYPE_1__ options; } ;

/* Variables and functions */
 scalar_t__ QETH_CQ_ENABLED ; 

__attribute__((used)) static inline int qeth_is_cq(struct qeth_card *card, unsigned int queue)
{
	return card->options.cq == QETH_CQ_ENABLED &&
	    card->qdio.c_q != NULL &&
	    queue != 0 &&
	    queue == card->qdio.no_in_queues - 1;
}