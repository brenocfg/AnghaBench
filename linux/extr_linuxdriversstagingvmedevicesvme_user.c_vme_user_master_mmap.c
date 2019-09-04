#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vme_user_vma_priv {unsigned int minor; int /*<<< orphan*/  refcnt; } ;
struct vm_area_struct {struct vme_user_vma_priv* vm_private_data; int /*<<< orphan*/ * vm_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  mmap_count; int /*<<< orphan*/  resource; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* image ; 
 struct vme_user_vma_priv* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int vme_master_mmap (int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 int /*<<< orphan*/  vme_user_vm_ops ; 

__attribute__((used)) static int vme_user_master_mmap(unsigned int minor, struct vm_area_struct *vma)
{
	int err;
	struct vme_user_vma_priv *vma_priv;

	mutex_lock(&image[minor].mutex);

	err = vme_master_mmap(image[minor].resource, vma);
	if (err) {
		mutex_unlock(&image[minor].mutex);
		return err;
	}

	vma_priv = kmalloc(sizeof(*vma_priv), GFP_KERNEL);
	if (!vma_priv) {
		mutex_unlock(&image[minor].mutex);
		return -ENOMEM;
	}

	vma_priv->minor = minor;
	refcount_set(&vma_priv->refcnt, 1);
	vma->vm_ops = &vme_user_vm_ops;
	vma->vm_private_data = vma_priv;

	image[minor].mmap_count++;

	mutex_unlock(&image[minor].mutex);

	return 0;
}