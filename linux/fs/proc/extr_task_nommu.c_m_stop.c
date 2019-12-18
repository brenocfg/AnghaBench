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
struct seq_file {struct proc_maps_private* private; } ;
struct proc_maps_private {int /*<<< orphan*/ * task; TYPE_1__* mm; } ;
struct TYPE_2__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (void*) ; 
 int /*<<< orphan*/  mmput (TYPE_1__*) ; 
 int /*<<< orphan*/  put_task_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void m_stop(struct seq_file *m, void *_vml)
{
	struct proc_maps_private *priv = m->private;

	if (!IS_ERR_OR_NULL(_vml)) {
		up_read(&priv->mm->mmap_sem);
		mmput(priv->mm);
	}
	if (priv->task) {
		put_task_struct(priv->task);
		priv->task = NULL;
	}
}