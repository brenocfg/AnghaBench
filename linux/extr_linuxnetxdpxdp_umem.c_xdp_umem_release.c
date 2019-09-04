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
struct xdp_umem {struct xdp_umem* pages; int /*<<< orphan*/  pid; int /*<<< orphan*/ * cq; int /*<<< orphan*/ * fq; } ;
struct task_struct {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIDTYPE_PID ; 
 struct task_struct* get_pid_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mm_struct* get_task_mm (struct task_struct*) ; 
 int /*<<< orphan*/  kfree (struct xdp_umem*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  xdp_umem_clear_dev (struct xdp_umem*) ; 
 int /*<<< orphan*/  xdp_umem_unaccount_pages (struct xdp_umem*) ; 
 int /*<<< orphan*/  xdp_umem_unpin_pages (struct xdp_umem*) ; 
 int /*<<< orphan*/  xskq_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xdp_umem_release(struct xdp_umem *umem)
{
	struct task_struct *task;
	struct mm_struct *mm;

	xdp_umem_clear_dev(umem);

	if (umem->fq) {
		xskq_destroy(umem->fq);
		umem->fq = NULL;
	}

	if (umem->cq) {
		xskq_destroy(umem->cq);
		umem->cq = NULL;
	}

	xdp_umem_unpin_pages(umem);

	task = get_pid_task(umem->pid, PIDTYPE_PID);
	put_pid(umem->pid);
	if (!task)
		goto out;
	mm = get_task_mm(task);
	put_task_struct(task);
	if (!mm)
		goto out;

	mmput(mm);
	kfree(umem->pages);
	umem->pages = NULL;

	xdp_umem_unaccount_pages(umem);
out:
	kfree(umem);
}