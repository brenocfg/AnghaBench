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
struct sbq_wait_state {int /*<<< orphan*/  wait; } ;
struct sbitmap_queue {int /*<<< orphan*/  wake_index; struct sbq_wait_state* ws; } ;

/* Variables and functions */
 int SBQ_WAIT_QUEUES ; 
 int /*<<< orphan*/  atomic_cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int sbq_index_inc (int) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sbq_wait_state *sbq_wake_ptr(struct sbitmap_queue *sbq)
{
	int i, wake_index;

	wake_index = atomic_read(&sbq->wake_index);
	for (i = 0; i < SBQ_WAIT_QUEUES; i++) {
		struct sbq_wait_state *ws = &sbq->ws[wake_index];

		if (waitqueue_active(&ws->wait)) {
			int o = atomic_read(&sbq->wake_index);

			if (wake_index != o)
				atomic_cmpxchg(&sbq->wake_index, o, wake_index);
			return ws;
		}

		wake_index = sbq_index_inc(wake_index);
	}

	return NULL;
}