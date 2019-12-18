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
struct vm_area_struct {int /*<<< orphan*/  vm_rb; } ;

/* Variables and functions */
 int /*<<< orphan*/  vma_gap_callbacks_propagate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vma_gap_update(struct vm_area_struct *vma)
{
	/*
	 * As it turns out, RB_DECLARE_CALLBACKS_MAX() already created
	 * a callback function that does exactly what we want.
	 */
	vma_gap_callbacks_propagate(&vma->vm_rb, NULL);
}