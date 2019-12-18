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
struct vm_area_struct {scalar_t__ vm_next; } ;
struct proc_maps_private {struct vm_area_struct* tail_vma; } ;

/* Variables and functions */

__attribute__((used)) static struct vm_area_struct *
m_next_vma(struct proc_maps_private *priv, struct vm_area_struct *vma)
{
	if (vma == priv->tail_vma)
		return NULL;
	return vma->vm_next ?: priv->tail_vma;
}