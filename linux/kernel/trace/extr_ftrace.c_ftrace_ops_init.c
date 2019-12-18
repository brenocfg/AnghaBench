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
struct TYPE_2__ {int /*<<< orphan*/  regex_lock; } ;
struct ftrace_ops {int flags; TYPE_1__ local_hash; TYPE_1__* func_hash; } ;

/* Variables and functions */
 int FTRACE_OPS_FL_INITIALIZED ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ftrace_ops_init(struct ftrace_ops *ops)
{
#ifdef CONFIG_DYNAMIC_FTRACE
	if (!(ops->flags & FTRACE_OPS_FL_INITIALIZED)) {
		mutex_init(&ops->local_hash.regex_lock);
		ops->func_hash = &ops->local_hash;
		ops->flags |= FTRACE_OPS_FL_INITIALIZED;
	}
#endif
}