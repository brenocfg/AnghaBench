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
struct tracepoint_func {int dummy; } ;
struct tracepoint {int (* regfunc ) () ;int /*<<< orphan*/  key; int /*<<< orphan*/  funcs; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct tracepoint_func*) ; 
 int PTR_ERR (struct tracepoint_func*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct tracepoint_func* func_add (struct tracepoint_func**,struct tracepoint_func*,int) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct tracepoint_func*) ; 
 struct tracepoint_func* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_probes (struct tracepoint_func*) ; 
 int /*<<< orphan*/  static_key_enabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  static_key_slow_inc (int /*<<< orphan*/ *) ; 
 int stub1 () ; 
 int /*<<< orphan*/  tracepoints_mutex ; 

__attribute__((used)) static int tracepoint_add_func(struct tracepoint *tp,
			       struct tracepoint_func *func, int prio)
{
	struct tracepoint_func *old, *tp_funcs;
	int ret;

	if (tp->regfunc && !static_key_enabled(&tp->key)) {
		ret = tp->regfunc();
		if (ret < 0)
			return ret;
	}

	tp_funcs = rcu_dereference_protected(tp->funcs,
			lockdep_is_held(&tracepoints_mutex));
	old = func_add(&tp_funcs, func, prio);
	if (IS_ERR(old)) {
		WARN_ON_ONCE(PTR_ERR(old) != -ENOMEM);
		return PTR_ERR(old);
	}

	/*
	 * rcu_assign_pointer has as smp_store_release() which makes sure
	 * that the new probe callbacks array is consistent before setting
	 * a pointer to it.  This array is referenced by __DO_TRACE from
	 * include/linux/tracepoint.h using rcu_dereference_sched().
	 */
	rcu_assign_pointer(tp->funcs, tp_funcs);
	if (!static_key_enabled(&tp->key))
		static_key_slow_inc(&tp->key);
	release_probes(old);
	return 0;
}