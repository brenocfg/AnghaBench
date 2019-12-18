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
typedef  void vm_area_struct ;
struct seq_file {struct proc_maps_private* private; } ;
struct proc_maps_private {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 void* m_next_vma (struct proc_maps_private*,void*) ; 
 int /*<<< orphan*/  vma_stop (struct proc_maps_private*) ; 

__attribute__((used)) static void *m_next(struct seq_file *m, void *v, loff_t *pos)
{
	struct proc_maps_private *priv = m->private;
	struct vm_area_struct *next;

	(*pos)++;
	next = m_next_vma(priv, v);
	if (!next)
		vma_stop(priv);
	return next;
}