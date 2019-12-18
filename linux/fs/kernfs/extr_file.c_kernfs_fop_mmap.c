#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {TYPE_1__* vm_ops; struct file* vm_file; } ;
struct kernfs_ops {int (* mmap ) (struct kernfs_open_file*,struct vm_area_struct*) ;} ;
struct kernfs_open_file {int mmapped; int /*<<< orphan*/  mutex; TYPE_2__* kn; TYPE_1__* vm_ops; } ;
struct file {int dummy; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_5__ {scalar_t__ close; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int KERNFS_HAS_MMAP ; 
 int /*<<< orphan*/  kernfs_get_active (TYPE_2__*) ; 
 struct kernfs_open_file* kernfs_of (struct file*) ; 
 struct kernfs_ops* kernfs_ops (TYPE_2__*) ; 
 int /*<<< orphan*/  kernfs_put_active (TYPE_2__*) ; 
 TYPE_1__ kernfs_vm_ops ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct kernfs_open_file*,struct vm_area_struct*) ; 

__attribute__((used)) static int kernfs_fop_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct kernfs_open_file *of = kernfs_of(file);
	const struct kernfs_ops *ops;
	int rc;

	/*
	 * mmap path and of->mutex are prone to triggering spurious lockdep
	 * warnings and we don't want to add spurious locking dependency
	 * between the two.  Check whether mmap is actually implemented
	 * without grabbing @of->mutex by testing HAS_MMAP flag.  See the
	 * comment in kernfs_file_open() for more details.
	 */
	if (!(of->kn->flags & KERNFS_HAS_MMAP))
		return -ENODEV;

	mutex_lock(&of->mutex);

	rc = -ENODEV;
	if (!kernfs_get_active(of->kn))
		goto out_unlock;

	ops = kernfs_ops(of->kn);
	rc = ops->mmap(of, vma);
	if (rc)
		goto out_put;

	/*
	 * PowerPC's pci_mmap of legacy_mem uses shmem_zero_setup()
	 * to satisfy versions of X which crash if the mmap fails: that
	 * substitutes a new vm_file, and we don't then want bin_vm_ops.
	 */
	if (vma->vm_file != file)
		goto out_put;

	rc = -EINVAL;
	if (of->mmapped && of->vm_ops != vma->vm_ops)
		goto out_put;

	/*
	 * It is not possible to successfully wrap close.
	 * So error if someone is trying to use close.
	 */
	rc = -EINVAL;
	if (vma->vm_ops && vma->vm_ops->close)
		goto out_put;

	rc = 0;
	of->mmapped = true;
	of->vm_ops = vma->vm_ops;
	vma->vm_ops = &kernfs_vm_ops;
out_put:
	kernfs_put_active(of->kn);
out_unlock:
	mutex_unlock(&of->mutex);

	return rc;
}