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
struct seq_file {struct proc_maps_private* private; } ;
typedef  void rb_node ;
struct proc_maps_private {struct mm_struct* mm; int /*<<< orphan*/  task; int /*<<< orphan*/  inode; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; int /*<<< orphan*/  mm_rb; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESRCH ; 
 scalar_t__ down_read_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_proc_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmget_not_zero (struct mm_struct*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 void* rb_first (int /*<<< orphan*/ *) ; 
 void* rb_next (void*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *m_start(struct seq_file *m, loff_t *pos)
{
	struct proc_maps_private *priv = m->private;
	struct mm_struct *mm;
	struct rb_node *p;
	loff_t n = *pos;

	/* pin the task and mm whilst we play with them */
	priv->task = get_proc_task(priv->inode);
	if (!priv->task)
		return ERR_PTR(-ESRCH);

	mm = priv->mm;
	if (!mm || !mmget_not_zero(mm))
		return NULL;

	if (down_read_killable(&mm->mmap_sem)) {
		mmput(mm);
		return ERR_PTR(-EINTR);
	}

	/* start from the Nth VMA */
	for (p = rb_first(&mm->mm_rb); p; p = rb_next(p))
		if (n-- == 0)
			return p;

	up_read(&mm->mmap_sem);
	mmput(mm);
	return NULL;
}