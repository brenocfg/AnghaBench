#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cs_etm_queue {int cpu; int /*<<< orphan*/  tid; } ;
struct cs_etm_auxtrace {int dummy; } ;
struct auxtrace_queue {int cpu; int /*<<< orphan*/  tid; struct cs_etm_queue* priv; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct cs_etm_queue* cs_etm__alloc_queue (struct cs_etm_auxtrace*,unsigned int) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cs_etm__setup_queue(struct cs_etm_auxtrace *etm,
			       struct auxtrace_queue *queue,
			       unsigned int queue_nr)
{
	struct cs_etm_queue *etmq = queue->priv;

	if (list_empty(&queue->head) || etmq)
		return 0;

	etmq = cs_etm__alloc_queue(etm, queue_nr);

	if (!etmq)
		return -ENOMEM;

	queue->priv = etmq;

	if (queue->cpu != -1)
		etmq->cpu = queue->cpu;

	etmq->tid = queue->tid;

	return 0;
}