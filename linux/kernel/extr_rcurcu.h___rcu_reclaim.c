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
struct rcu_head {int /*<<< orphan*/  (* func ) (struct rcu_head*) ;} ;
typedef  int /*<<< orphan*/  (* rcu_callback_t ) (struct rcu_head*) ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/  (*) (struct rcu_head*),int /*<<< orphan*/  (*) (struct rcu_head*)) ; 
 scalar_t__ __is_kfree_rcu_offset (unsigned long) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  rcu_callback_map ; 
 int /*<<< orphan*/  rcu_lock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_lock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rcu_invoke_callback (char const*,struct rcu_head*) ; 
 int /*<<< orphan*/  trace_rcu_invoke_kfree_callback (char const*,struct rcu_head*,unsigned long) ; 

__attribute__((used)) static inline bool __rcu_reclaim(const char *rn, struct rcu_head *head)
{
	rcu_callback_t f;
	unsigned long offset = (unsigned long)head->func;

	rcu_lock_acquire(&rcu_callback_map);
	if (__is_kfree_rcu_offset(offset)) {
		trace_rcu_invoke_kfree_callback(rn, head, offset);
		kfree((void *)head - offset);
		rcu_lock_release(&rcu_callback_map);
		return true;
	} else {
		trace_rcu_invoke_callback(rn, head);
		f = head->func;
		WRITE_ONCE(head->func, (rcu_callback_t)0L);
		f(head);
		rcu_lock_release(&rcu_callback_map);
		return false;
	}
}