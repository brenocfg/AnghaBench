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
struct vm_area_struct {int vm_flags; struct fb_info* vm_private_data; int /*<<< orphan*/ * vm_ops; } ;
struct fb_info {int flags; } ;

/* Variables and functions */
 int FBINFO_VIRTFB ; 
 int VM_DONTDUMP ; 
 int VM_DONTEXPAND ; 
 int VM_IO ; 
 int /*<<< orphan*/  fb_deferred_io_vm_ops ; 

int fb_deferred_io_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
	vma->vm_ops = &fb_deferred_io_vm_ops;
	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	if (!(info->flags & FBINFO_VIRTFB))
		vma->vm_flags |= VM_IO;
	vma->vm_private_data = info;
	return 0;
}