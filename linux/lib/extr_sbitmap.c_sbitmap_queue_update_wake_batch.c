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
struct sbitmap_queue {unsigned int wake_batch; TYPE_1__* ws; } ;
struct TYPE_2__ {int /*<<< orphan*/  wait_cnt; } ;

/* Variables and functions */
 int SBQ_WAIT_QUEUES ; 
 int /*<<< orphan*/  WRITE_ONCE (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 unsigned int sbq_calc_wake_batch (struct sbitmap_queue*,unsigned int) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static void sbitmap_queue_update_wake_batch(struct sbitmap_queue *sbq,
					    unsigned int depth)
{
	unsigned int wake_batch = sbq_calc_wake_batch(sbq, depth);
	int i;

	if (sbq->wake_batch != wake_batch) {
		WRITE_ONCE(sbq->wake_batch, wake_batch);
		/*
		 * Pairs with the memory barrier in sbitmap_queue_wake_up()
		 * to ensure that the batch size is updated before the wait
		 * counts.
		 */
		smp_mb();
		for (i = 0; i < SBQ_WAIT_QUEUES; i++)
			atomic_set(&sbq->ws[i].wait_cnt, 1);
	}
}