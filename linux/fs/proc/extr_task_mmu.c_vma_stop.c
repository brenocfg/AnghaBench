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
struct proc_maps_private {struct mm_struct* mm; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  release_task_mempolicy (struct proc_maps_private*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vma_stop(struct proc_maps_private *priv)
{
	struct mm_struct *mm = priv->mm;

	release_task_mempolicy(priv);
	up_read(&mm->mmap_sem);
	mmput(mm);
}