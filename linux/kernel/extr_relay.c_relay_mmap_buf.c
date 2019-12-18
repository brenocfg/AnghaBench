#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; struct rchan_buf* vm_private_data; int /*<<< orphan*/  vm_flags; int /*<<< orphan*/ * vm_ops; struct file* vm_file; } ;
struct rchan_buf {TYPE_2__* chan; } ;
struct file {int dummy; } ;
struct TYPE_4__ {TYPE_1__* cb; scalar_t__ alloc_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* buf_mapped ) (struct rchan_buf*,struct file*) ;} ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int /*<<< orphan*/  VM_DONTEXPAND ; 
 int /*<<< orphan*/  relay_file_mmap_ops ; 
 int /*<<< orphan*/  stub1 (struct rchan_buf*,struct file*) ; 

__attribute__((used)) static int relay_mmap_buf(struct rchan_buf *buf, struct vm_area_struct *vma)
{
	unsigned long length = vma->vm_end - vma->vm_start;
	struct file *filp = vma->vm_file;

	if (!buf)
		return -EBADF;

	if (length != (unsigned long)buf->chan->alloc_size)
		return -EINVAL;

	vma->vm_ops = &relay_file_mmap_ops;
	vma->vm_flags |= VM_DONTEXPAND;
	vma->vm_private_data = buf;
	buf->chan->cb->buf_mapped(buf, filp);

	return 0;
}