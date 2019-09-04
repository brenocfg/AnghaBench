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
typedef  scalar_t__ ulong ;
struct vm_area_struct {scalar_t__ vm_end; scalar_t__ vm_start; int /*<<< orphan*/  vm_page_prot; } ;
struct TYPE_5__ {scalar_t__ permissions; } ;
struct gasket_driver_desc {TYPE_2__ coherent_buffer_description; } ;
struct TYPE_6__ {scalar_t__ const length_bytes; int phys_base; } ;
struct gasket_dev {TYPE_3__ coherent_buffer; int /*<<< orphan*/  dev; TYPE_1__* internal_desc; } ;
struct TYPE_4__ {struct gasket_driver_desc* driver_desc; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gasket_mmap_has_permissions (struct gasket_dev*,struct vm_area_struct*,scalar_t__) ; 
 int /*<<< orphan*/  gasket_set_user_virt (struct gasket_dev*,scalar_t__ const,int,scalar_t__) ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int remap_pfn_range (struct vm_area_struct*,scalar_t__,int,scalar_t__ const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_gasket_mmap_exit (int) ; 

__attribute__((used)) static int gasket_mmap_coherent(struct gasket_dev *gasket_dev,
				struct vm_area_struct *vma)
{
	const struct gasket_driver_desc *driver_desc =
		gasket_dev->internal_desc->driver_desc;
	const ulong requested_length = vma->vm_end - vma->vm_start;
	int ret;
	ulong permissions;

	if (requested_length == 0 || requested_length >
	    gasket_dev->coherent_buffer.length_bytes) {
		trace_gasket_mmap_exit(-EINVAL);
		return -EINVAL;
	}

	permissions = driver_desc->coherent_buffer_description.permissions;
	if (!gasket_mmap_has_permissions(gasket_dev, vma, permissions)) {
		dev_err(gasket_dev->dev, "Permission checking failed.\n");
		trace_gasket_mmap_exit(-EPERM);
		return -EPERM;
	}

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	ret = remap_pfn_range(vma, vma->vm_start,
			      (gasket_dev->coherent_buffer.phys_base) >>
			      PAGE_SHIFT, requested_length, vma->vm_page_prot);
	if (ret) {
		dev_err(gasket_dev->dev, "Error remapping PFN range err=%d.\n",
			ret);
		trace_gasket_mmap_exit(ret);
		return ret;
	}

	/* Record the user virtual to dma_address mapping that was
	 * created by the kernel.
	 */
	gasket_set_user_virt(gasket_dev, requested_length,
			     gasket_dev->coherent_buffer.phys_base,
			     vma->vm_start);
	return 0;
}