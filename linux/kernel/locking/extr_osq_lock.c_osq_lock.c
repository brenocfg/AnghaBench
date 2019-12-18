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
struct optimistic_spin_node {int cpu; struct optimistic_spin_node* next; struct optimistic_spin_node* prev; struct optimistic_spin_node* locked; } ;

/* Variables and functions */
 int OSQ_UNLOCKED_VAL ; 
 struct optimistic_spin_node* READ_ONCE (struct optimistic_spin_node*) ; 
 int /*<<< orphan*/  WRITE_ONCE (struct optimistic_spin_node*,struct optimistic_spin_node*) ; 
 int atomic_xchg (int /*<<< orphan*/ *,int) ; 
 struct optimistic_spin_node* cmpxchg (struct optimistic_spin_node**,struct optimistic_spin_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 struct optimistic_spin_node* decode_cpu (int) ; 
 int encode_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  node_cpu (struct optimistic_spin_node*) ; 
 int /*<<< orphan*/  osq_node ; 
 struct optimistic_spin_node* osq_wait_next (struct optimistic_spin_queue*,struct optimistic_spin_node*,struct optimistic_spin_node*) ; 
 scalar_t__ smp_load_acquire (struct optimistic_spin_node**) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 struct optimistic_spin_node* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ vcpu_is_preempted (int /*<<< orphan*/ ) ; 

bool osq_lock(struct optimistic_spin_queue *lock)
{
	struct optimistic_spin_node *node = this_cpu_ptr(&osq_node);
	struct optimistic_spin_node *prev, *next;
	int curr = encode_cpu(smp_processor_id());
	int old;

	node->locked = 0;
	node->next = NULL;
	node->cpu = curr;

	/*
	 * We need both ACQUIRE (pairs with corresponding RELEASE in
	 * unlock() uncontended, or fastpath) and RELEASE (to publish
	 * the node fields we just initialised) semantics when updating
	 * the lock tail.
	 */
	old = atomic_xchg(&lock->tail, curr);
	if (old == OSQ_UNLOCKED_VAL)
		return true;

	prev = decode_cpu(old);
	node->prev = prev;

	/*
	 * osq_lock()			unqueue
	 *
	 * node->prev = prev		osq_wait_next()
	 * WMB				MB
	 * prev->next = node		next->prev = prev // unqueue-C
	 *
	 * Here 'node->prev' and 'next->prev' are the same variable and we need
	 * to ensure these stores happen in-order to avoid corrupting the list.
	 */
	smp_wmb();

	WRITE_ONCE(prev->next, node);

	/*
	 * Normally @prev is untouchable after the above store; because at that
	 * moment unlock can proceed and wipe the node element from stack.
	 *
	 * However, since our nodes are static per-cpu storage, we're
	 * guaranteed their existence -- this allows us to apply
	 * cmpxchg in an attempt to undo our queueing.
	 */

	while (!READ_ONCE(node->locked)) {
		/*
		 * If we need to reschedule bail... so we can block.
		 * Use vcpu_is_preempted() to avoid waiting for a preempted
		 * lock holder:
		 */
		if (need_resched() || vcpu_is_preempted(node_cpu(node->prev)))
			goto unqueue;

		cpu_relax();
	}
	return true;

unqueue:
	/*
	 * Step - A  -- stabilize @prev
	 *
	 * Undo our @prev->next assignment; this will make @prev's
	 * unlock()/unqueue() wait for a next pointer since @lock points to us
	 * (or later).
	 */

	for (;;) {
		if (prev->next == node &&
		    cmpxchg(&prev->next, node, NULL) == node)
			break;

		/*
		 * We can only fail the cmpxchg() racing against an unlock(),
		 * in which case we should observe @node->locked becomming
		 * true.
		 */
		if (smp_load_acquire(&node->locked))
			return true;

		cpu_relax();

		/*
		 * Or we race against a concurrent unqueue()'s step-B, in which
		 * case its step-C will write us a new @node->prev pointer.
		 */
		prev = READ_ONCE(node->prev);
	}

	/*
	 * Step - B -- stabilize @next
	 *
	 * Similar to unlock(), wait for @node->next or move @lock from @node
	 * back to @prev.
	 */

	next = osq_wait_next(lock, node, prev);
	if (!next)
		return false;

	/*
	 * Step - C -- unlink
	 *
	 * @prev is stable because its still waiting for a new @prev->next
	 * pointer, @next is stable because our @node->next pointer is NULL and
	 * it will wait in Step-A.
	 */

	WRITE_ONCE(next->prev, prev);
	WRITE_ONCE(prev->next, next);

	return false;
}