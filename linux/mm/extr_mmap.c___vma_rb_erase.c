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
struct rb_root {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_erase_augmented (int /*<<< orphan*/ *,struct rb_root*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vma_gap_callbacks ; 

__attribute__((used)) static void __vma_rb_erase(struct vm_area_struct *vma, struct rb_root *root)
{
	/*
	 * Note rb_erase_augmented is a fairly large inline function,
	 * so make sure we instantiate it only once with our desired
	 * augmented rbtree callbacks.
	 */
	rb_erase_augmented(&vma->vm_rb, root, &vma_gap_callbacks);
}