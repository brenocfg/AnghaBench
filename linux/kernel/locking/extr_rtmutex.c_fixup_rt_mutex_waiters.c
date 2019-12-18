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
struct rt_mutex {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 unsigned long READ_ONCE (unsigned long) ; 
 unsigned long RT_MUTEX_HAS_WAITERS ; 
 int /*<<< orphan*/  WRITE_ONCE (unsigned long,unsigned long) ; 
 scalar_t__ rt_mutex_has_waiters (struct rt_mutex*) ; 

__attribute__((used)) static void fixup_rt_mutex_waiters(struct rt_mutex *lock)
{
	unsigned long owner, *p = (unsigned long *) &lock->owner;

	if (rt_mutex_has_waiters(lock))
		return;

	/*
	 * The rbtree has no waiters enqueued, now make sure that the
	 * lock->owner still has the waiters bit set, otherwise the
	 * following can happen:
	 *
	 * CPU 0	CPU 1		CPU2
	 * l->owner=T1
	 *		rt_mutex_lock(l)
	 *		lock(l->lock)
	 *		l->owner = T1 | HAS_WAITERS;
	 *		enqueue(T2)
	 *		boost()
	 *		  unlock(l->lock)
	 *		block()
	 *
	 *				rt_mutex_lock(l)
	 *				lock(l->lock)
	 *				l->owner = T1 | HAS_WAITERS;
	 *				enqueue(T3)
	 *				boost()
	 *				  unlock(l->lock)
	 *				block()
	 *		signal(->T2)	signal(->T3)
	 *		lock(l->lock)
	 *		dequeue(T2)
	 *		deboost()
	 *		  unlock(l->lock)
	 *				lock(l->lock)
	 *				dequeue(T3)
	 *				 ==> wait list is empty
	 *				deboost()
	 *				 unlock(l->lock)
	 *		lock(l->lock)
	 *		fixup_rt_mutex_waiters()
	 *		  if (wait_list_empty(l) {
	 *		    l->owner = owner
	 *		    owner = l->owner & ~HAS_WAITERS;
	 *		      ==> l->owner = T1
	 *		  }
	 *				lock(l->lock)
	 * rt_mutex_unlock(l)		fixup_rt_mutex_waiters()
	 *				  if (wait_list_empty(l) {
	 *				    owner = l->owner & ~HAS_WAITERS;
	 * cmpxchg(l->owner, T1, NULL)
	 *  ===> Success (l->owner = NULL)
	 *
	 *				    l->owner = owner
	 *				      ==> l->owner = T1
	 *				  }
	 *
	 * With the check for the waiter bit in place T3 on CPU2 will not
	 * overwrite. All tasks fiddling with the waiters bit are
	 * serialized by l->lock, so nothing else can modify the waiters
	 * bit. If the bit is set then nothing can change l->owner either
	 * so the simple RMW is safe. The cmpxchg() will simply fail if it
	 * happens in the middle of the RMW because the waiters bit is
	 * still set.
	 */
	owner = READ_ONCE(*p);
	if (owner & RT_MUTEX_HAS_WAITERS)
		WRITE_ONCE(*p, owner & ~RT_MUTEX_HAS_WAITERS);
}