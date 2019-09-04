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
struct vm_area_struct {int vm_flags; int /*<<< orphan*/  vm_start; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int VM_DONTDUMP ; 
 int VM_DONTEXPAND ; 
 int /*<<< orphan*/  videomemory ; 

__attribute__((used)) static int mc68x328fb_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
#ifndef MMU
	/* this is uClinux (no MMU) specific code */

	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_start = videomemory;

	return 0;
#else
	return -EINVAL;
#endif
}