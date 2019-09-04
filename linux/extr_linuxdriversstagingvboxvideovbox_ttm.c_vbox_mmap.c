#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {scalar_t__ vm_pgoff; } ;
struct TYPE_6__ {int /*<<< orphan*/  bdev; } ;
struct vbox_private {TYPE_3__ ttm; } ;
struct file {struct drm_file* private_data; } ;
struct drm_file {TYPE_2__* minor; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {struct vbox_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ DRM_FILE_PAGE_OFFSET ; 
 int EINVAL ; 
 int ttm_bo_mmap (struct file*,struct vm_area_struct*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int vbox_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct drm_file *file_priv;
	struct vbox_private *vbox;

	if (unlikely(vma->vm_pgoff < DRM_FILE_PAGE_OFFSET))
		return -EINVAL;

	file_priv = filp->private_data;
	vbox = file_priv->minor->dev->dev_private;

	return ttm_bo_mmap(filp, vma, &vbox->ttm.bdev);
}