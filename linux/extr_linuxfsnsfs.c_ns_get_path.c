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
struct task_struct {int dummy; } ;
struct proc_ns_operations {int dummy; } ;
struct path {int dummy; } ;
struct ns_get_path_task_args {struct task_struct* task; struct proc_ns_operations const* ns_ops; } ;

/* Variables and functions */
 void* ns_get_path_cb (struct path*,int /*<<< orphan*/ ,struct ns_get_path_task_args*) ; 
 int /*<<< orphan*/  ns_get_path_task ; 

void *ns_get_path(struct path *path, struct task_struct *task,
		  const struct proc_ns_operations *ns_ops)
{
	struct ns_get_path_task_args args = {
		.ns_ops	= ns_ops,
		.task	= task,
	};

	return ns_get_path_cb(path, ns_get_path_task, &args);
}