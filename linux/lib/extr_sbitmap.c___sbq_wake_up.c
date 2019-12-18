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
struct sbq_wait_state {int /*<<< orphan*/  wait; int /*<<< orphan*/  wait_cnt; } ;
struct sbitmap_queue {int /*<<< orphan*/  wake_index; int /*<<< orphan*/  wake_batch; } ;

/* Variables and functions */
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 int atomic_cmpxchg (int /*<<< orphan*/ *,int,unsigned int) ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbq_index_atomic_inc (int /*<<< orphan*/ *) ; 
 struct sbq_wait_state* sbq_wake_ptr (struct sbitmap_queue*) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 int /*<<< orphan*/  wake_up_nr (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static bool __sbq_wake_up(struct sbitmap_queue *sbq)
{
	struct sbq_wait_state *ws;
	unsigned int wake_batch;
	int wait_cnt;

	ws = sbq_wake_ptr(sbq);
	if (!ws)
		return false;

	wait_cnt = atomic_dec_return(&ws->wait_cnt);
	if (wait_cnt <= 0) {
		int ret;

		wake_batch = READ_ONCE(sbq->wake_batch);

		/*
		 * Pairs with the memory barrier in sbitmap_queue_resize() to
		 * ensure that we see the batch size update before the wait
		 * count is reset.
		 */
		smp_mb__before_atomic();

		/*
		 * For concurrent callers of this, the one that failed the
		 * atomic_cmpxhcg() race should call this function again
		 * to wakeup a new batch on a different 'ws'.
		 */
		ret = atomic_cmpxchg(&ws->wait_cnt, wait_cnt, wake_batch);
		if (ret == wait_cnt) {
			sbq_index_atomic_inc(&sbq->wake_index);
			wake_up_nr(&ws->wait, wake_batch);
			return false;
		}

		return true;
	}

	return false;
}