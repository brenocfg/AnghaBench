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
struct task_struct {struct io_context* io_context; } ;
struct io_context {int /*<<< orphan*/  ioprio; } ;
struct TYPE_2__ {struct io_context* io_context; } ;

/* Variables and functions */
 unsigned long CLONE_IO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 TYPE_1__* current ; 
 struct io_context* get_task_io_context (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc_task_link (struct io_context*) ; 
 scalar_t__ ioprio_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_io_context (struct io_context*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int copy_io(unsigned long clone_flags, struct task_struct *tsk)
{
#ifdef CONFIG_BLOCK
	struct io_context *ioc = current->io_context;
	struct io_context *new_ioc;

	if (!ioc)
		return 0;
	/*
	 * Share io context with parent, if CLONE_IO is set
	 */
	if (clone_flags & CLONE_IO) {
		ioc_task_link(ioc);
		tsk->io_context = ioc;
	} else if (ioprio_valid(ioc->ioprio)) {
		new_ioc = get_task_io_context(tsk, GFP_KERNEL, NUMA_NO_NODE);
		if (unlikely(!new_ioc))
			return -ENOMEM;

		new_ioc->ioprio = ioc->ioprio;
		put_io_context(new_ioc);
	}
#endif
	return 0;
}