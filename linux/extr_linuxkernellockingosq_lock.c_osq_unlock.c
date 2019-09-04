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
struct optimistic_spin_queue {int /*<<< orphan*/  tail; } ;
struct optimistic_spin_node {int /*<<< orphan*/  locked; int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSQ_UNLOCKED_VAL ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int atomic_cmpxchg_release (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int encode_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  osq_node ; 
 struct optimistic_spin_node* osq_wait_next (struct optimistic_spin_queue*,struct optimistic_spin_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 struct optimistic_spin_node* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 struct optimistic_spin_node* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void osq_unlock(struct optimistic_spin_queue *lock)
{
	struct optimistic_spin_node *node, *next;
	int curr = encode_cpu(smp_processor_id());

	/*
	 * Fast path for the uncontended case.
	 */
	if (likely(atomic_cmpxchg_release(&lock->tail, curr,
					  OSQ_UNLOCKED_VAL) == curr))
		return;

	/*
	 * Second most likely case.
	 */
	node = this_cpu_ptr(&osq_node);
	next = xchg(&node->next, NULL);
	if (next) {
		WRITE_ONCE(next->locked, 1);
		return;
	}

	next = osq_wait_next(lock, node, NULL);
	if (next)
		WRITE_ONCE(next->locked, 1);
}