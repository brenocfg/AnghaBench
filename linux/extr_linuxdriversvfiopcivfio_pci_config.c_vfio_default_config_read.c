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
struct vfio_pci_device {struct pci_dev* pdev; scalar_t__ vconfig; } ;
struct perm_bits {scalar_t__ virt; } ;
struct pci_dev {int dummy; } ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 scalar_t__ cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__,int) ; 
 int vfio_user_config_read (struct pci_dev*,int,scalar_t__*,int) ; 

__attribute__((used)) static int vfio_default_config_read(struct vfio_pci_device *vdev, int pos,
				    int count, struct perm_bits *perm,
				    int offset, __le32 *val)
{
	__le32 virt = 0;

	memcpy(val, vdev->vconfig + pos, count);

	memcpy(&virt, perm->virt + offset, count);

	/* Any non-virtualized bits? */
	if (cpu_to_le32(~0U >> (32 - (count * 8))) != virt) {
		struct pci_dev *pdev = vdev->pdev;
		__le32 phys_val = 0;
		int ret;

		ret = vfio_user_config_read(pdev, pos, &phys_val, count);
		if (ret)
			return ret;

		*val = (phys_val & ~virt) | (*val & virt);
	}

	return count;
}