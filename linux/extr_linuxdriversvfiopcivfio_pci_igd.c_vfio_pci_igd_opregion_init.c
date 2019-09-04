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
typedef  int u32 ;
struct vfio_pci_device {scalar_t__ pci_config_map; int /*<<< orphan*/  pdev; scalar_t__ vconfig; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MEMREMAP_WB ; 
 scalar_t__ OPREGION_PCI_ADDR ; 
 int /*<<< orphan*/  OPREGION_SIGNATURE ; 
 int OPREGION_SIZE ; 
 int /*<<< orphan*/  PCI_CAP_ID_INVALID_VIRT ; 
 int PCI_VENDOR_ID_INTEL ; 
 int /*<<< orphan*/  VFIO_REGION_INFO_FLAG_READ ; 
 int /*<<< orphan*/  VFIO_REGION_SUBTYPE_INTEL_IGD_OPREGION ; 
 int VFIO_REGION_TYPE_PCI_VENDOR_TYPE ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (void*,int /*<<< orphan*/ ,int) ; 
 void* memremap (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memunmap (void*) ; 
 int pci_read_config_dword (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  vfio_pci_igd_regops ; 
 int vfio_pci_register_dev_region (struct vfio_pci_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int vfio_pci_igd_opregion_init(struct vfio_pci_device *vdev)
{
	__le32 *dwordp = (__le32 *)(vdev->vconfig + OPREGION_PCI_ADDR);
	u32 addr, size;
	void *base;
	int ret;

	ret = pci_read_config_dword(vdev->pdev, OPREGION_PCI_ADDR, &addr);
	if (ret)
		return ret;

	if (!addr || !(~addr))
		return -ENODEV;

	base = memremap(addr, OPREGION_SIZE, MEMREMAP_WB);
	if (!base)
		return -ENOMEM;

	if (memcmp(base, OPREGION_SIGNATURE, 16)) {
		memunmap(base);
		return -EINVAL;
	}

	size = le32_to_cpu(*(__le32 *)(base + 16));
	if (!size) {
		memunmap(base);
		return -EINVAL;
	}

	size *= 1024; /* In KB */

	if (size != OPREGION_SIZE) {
		memunmap(base);
		base = memremap(addr, size, MEMREMAP_WB);
		if (!base)
			return -ENOMEM;
	}

	ret = vfio_pci_register_dev_region(vdev,
		PCI_VENDOR_ID_INTEL | VFIO_REGION_TYPE_PCI_VENDOR_TYPE,
		VFIO_REGION_SUBTYPE_INTEL_IGD_OPREGION,
		&vfio_pci_igd_regops, size, VFIO_REGION_INFO_FLAG_READ, base);
	if (ret) {
		memunmap(base);
		return ret;
	}

	/* Fill vconfig with the hw value and virtualize register */
	*dwordp = cpu_to_le32(addr);
	memset(vdev->pci_config_map + OPREGION_PCI_ADDR,
	       PCI_CAP_ID_INVALID_VIRT, 4);

	return ret;
}