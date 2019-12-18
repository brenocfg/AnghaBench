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
struct proc_dir_entry {int /*<<< orphan*/  pde_unload_lock; TYPE_1__* proc_fops; } ;
struct pde_opener {int closing; struct completion* c; int /*<<< orphan*/  lh; struct file* file; } ;
struct file {int dummy; } ;
struct completion {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* release ) (int /*<<< orphan*/ ,struct file*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (struct completion) ; 
 struct completion c ; 
 int /*<<< orphan*/  complete (struct completion*) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct pde_opener*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pde_opener_cache ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct file*) ; 
 scalar_t__ unlikely (struct completion*) ; 
 int /*<<< orphan*/  wait_for_completion (struct completion*) ; 

__attribute__((used)) static void close_pdeo(struct proc_dir_entry *pde, struct pde_opener *pdeo)
{
	/*
	 * close() (proc_reg_release()) can't delete an entry and proceed:
	 * ->release hook needs to be available at the right moment.
	 *
	 * rmmod (remove_proc_entry() et al) can't delete an entry and proceed:
	 * "struct file" needs to be available at the right moment.
	 *
	 * Therefore, first process to enter this function does ->release() and
	 * signals its completion to the other process which does nothing.
	 */
	if (pdeo->closing) {
		/* somebody else is doing that, just wait */
		DECLARE_COMPLETION_ONSTACK(c);
		pdeo->c = &c;
		spin_unlock(&pde->pde_unload_lock);
		wait_for_completion(&c);
	} else {
		struct file *file;
		struct completion *c;

		pdeo->closing = true;
		spin_unlock(&pde->pde_unload_lock);
		file = pdeo->file;
		pde->proc_fops->release(file_inode(file), file);
		spin_lock(&pde->pde_unload_lock);
		/* After ->release. */
		list_del(&pdeo->lh);
		c = pdeo->c;
		spin_unlock(&pde->pde_unload_lock);
		if (unlikely(c))
			complete(c);
		kmem_cache_free(pde_opener_cache, pdeo);
	}
}