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
struct tracepoint {int /*<<< orphan*/  funcs; int /*<<< orphan*/  key; int /*<<< orphan*/  (* unregfunc ) () ;} ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct tracepoint_func*) ; 
 int PTR_ERR (struct tracepoint_func*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct tracepoint_func* func_remove (struct tracepoint_func**,struct tracepoint_func*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct tracepoint_func*) ; 
 struct tracepoint_func* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_probes (struct tracepoint_func*) ; 
 scalar_t__ static_key_enabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  static_key_slow_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  tracepoints_mutex ; 

__attribute__((used)) static int tracepoint_remove_func(struct tracepoint *tp,
		struct tracepoint_func *func)
{
	struct tracepoint_func *old, *tp_funcs;

	tp_funcs = rcu_dereference_protected(tp->funcs,
			lockdep_is_held(&tracepoints_mutex));
	old = func_remove(&tp_funcs, func);
	if (IS_ERR(old)) {
		WARN_ON_ONCE(PTR_ERR(old) != -ENOMEM);
		return PTR_ERR(old);
	}

	if (!tp_funcs) {
		/* Removed last function */
		if (tp->unregfunc && static_key_enabled(&tp->key))
			tp->unregfunc();

		if (static_key_enabled(&tp->key))
			static_key_slow_dec(&tp->key);
	}
	rcu_assign_pointer(tp->funcs, tp_funcs);
	release_probes(old);
	return 0;
}