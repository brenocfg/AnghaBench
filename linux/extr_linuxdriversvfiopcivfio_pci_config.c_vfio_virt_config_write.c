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
struct vfio_pci_device {scalar_t__ vconfig; } ;
struct perm_bits {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vfio_virt_config_write(struct vfio_pci_device *vdev, int pos,
				  int count, struct perm_bits *perm,
				  int offset, __le32 val)
{
	memcpy(vdev->vconfig + pos, &val, count);
	return count;
}