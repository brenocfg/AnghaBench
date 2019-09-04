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
struct vm_area_struct {scalar_t__ vm_start; scalar_t__ vm_end; struct mm_struct* vm_mm; } ;
struct mm_struct {scalar_t__ start_stack; } ;

/* Variables and functions */

__attribute__((used)) static int is_stack(struct vm_area_struct *vma)
{
	struct mm_struct *mm = vma->vm_mm;

	/*
	 * We make no effort to guess what a given thread considers to be
	 * its "stack".  It's not even well-defined for programs written
	 * languages like Go.
	 */
	return vma->vm_start <= mm->start_stack &&
		vma->vm_end >= mm->start_stack;
}