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
struct vm_area_struct {scalar_t__ vm_prev; } ;

/* Variables and functions */
 unsigned long vm_end_gap (scalar_t__) ; 
 unsigned long vm_start_gap (struct vm_area_struct*) ; 

__attribute__((used)) static inline unsigned long vma_compute_gap(struct vm_area_struct *vma)
{
	unsigned long gap, prev_end;

	/*
	 * Note: in the rare case of a VM_GROWSDOWN above a VM_GROWSUP, we
	 * allow two stack_guard_gaps between them here, and when choosing
	 * an unmapped area; whereas when expanding we only require one.
	 * That's a little inconsistent, but keeps the code here simpler.
	 */
	gap = vm_start_gap(vma);
	if (vma->vm_prev) {
		prev_end = vm_end_gap(vma->vm_prev);
		if (gap > prev_end)
			gap -= prev_end;
		else
			gap = 0;
	}
	return gap;
}