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
struct trace_array {struct ftrace_ops* ops; } ;
struct ftrace_ops {int flags; struct trace_array* private; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FTRACE_OPS_FL_PID ; 
 int FTRACE_OPS_FL_RECURSION_SAFE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  function_trace_call ; 
 struct ftrace_ops* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int allocate_ftrace_ops(struct trace_array *tr)
{
	struct ftrace_ops *ops;

	ops = kzalloc(sizeof(*ops), GFP_KERNEL);
	if (!ops)
		return -ENOMEM;

	/* Currently only the non stack verision is supported */
	ops->func = function_trace_call;
	ops->flags = FTRACE_OPS_FL_RECURSION_SAFE | FTRACE_OPS_FL_PID;

	tr->ops = ops;
	ops->private = tr;
	return 0;
}