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
struct mm_struct {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct mm_struct* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESRCH ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct mm_struct*) ; 
 unsigned int PTRACE_MODE_FSCREDS ; 
 struct task_struct* get_proc_task (struct inode*) ; 
 struct mm_struct* mm_access (struct task_struct*,unsigned int) ; 
 int /*<<< orphan*/  mmgrab (struct mm_struct*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 

struct mm_struct *proc_mem_open(struct inode *inode, unsigned int mode)
{
	struct task_struct *task = get_proc_task(inode);
	struct mm_struct *mm = ERR_PTR(-ESRCH);

	if (task) {
		mm = mm_access(task, mode | PTRACE_MODE_FSCREDS);
		put_task_struct(task);

		if (!IS_ERR_OR_NULL(mm)) {
			/* ensure this mm_struct can't be freed */
			mmgrab(mm);
			/* but do not pin its memory */
			mmput(mm);
		}
	}

	return mm;
}