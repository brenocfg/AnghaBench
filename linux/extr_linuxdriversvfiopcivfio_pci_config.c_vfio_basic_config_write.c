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
typedef  int u16 ;
struct vfio_pci_device {int virq_disabled; int bardirty; int /*<<< orphan*/ * vconfig; struct pci_dev* pdev; } ;
struct perm_bits {int dummy; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 size_t PCI_COMMAND ; 
 int PCI_COMMAND_INTX_DISABLE ; 
 int PCI_COMMAND_IO ; 
 int PCI_COMMAND_MEMORY ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 scalar_t__ is_bar (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int pci_user_read_config_word (struct pci_dev*,size_t,int*) ; 
 int /*<<< orphan*/  vfio_bar_restore (struct vfio_pci_device*) ; 
 int vfio_default_config_write (struct vfio_pci_device*,int,int,struct perm_bits*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ vfio_need_bar_restore (struct vfio_pci_device*) ; 
 int /*<<< orphan*/  vfio_pci_intx_mask (struct vfio_pci_device*) ; 
 int /*<<< orphan*/  vfio_pci_intx_unmask (struct vfio_pci_device*) ; 

__attribute__((used)) static int vfio_basic_config_write(struct vfio_pci_device *vdev, int pos,
				   int count, struct perm_bits *perm,
				   int offset, __le32 val)
{
	struct pci_dev *pdev = vdev->pdev;
	__le16 *virt_cmd;
	u16 new_cmd = 0;
	int ret;

	virt_cmd = (__le16 *)&vdev->vconfig[PCI_COMMAND];

	if (offset == PCI_COMMAND) {
		bool phys_mem, virt_mem, new_mem, phys_io, virt_io, new_io;
		u16 phys_cmd;

		ret = pci_user_read_config_word(pdev, PCI_COMMAND, &phys_cmd);
		if (ret)
			return ret;

		new_cmd = le32_to_cpu(val);

		phys_mem = !!(phys_cmd & PCI_COMMAND_MEMORY);
		virt_mem = !!(le16_to_cpu(*virt_cmd) & PCI_COMMAND_MEMORY);
		new_mem = !!(new_cmd & PCI_COMMAND_MEMORY);

		phys_io = !!(phys_cmd & PCI_COMMAND_IO);
		virt_io = !!(le16_to_cpu(*virt_cmd) & PCI_COMMAND_IO);
		new_io = !!(new_cmd & PCI_COMMAND_IO);

		/*
		 * If the user is writing mem/io enable (new_mem/io) and we
		 * think it's already enabled (virt_mem/io), but the hardware
		 * shows it disabled (phys_mem/io, then the device has
		 * undergone some kind of backdoor reset and needs to be
		 * restored before we allow it to enable the bars.
		 * SR-IOV devices will trigger this, but we catch them later
		 */
		if ((new_mem && virt_mem && !phys_mem) ||
		    (new_io && virt_io && !phys_io) ||
		    vfio_need_bar_restore(vdev))
			vfio_bar_restore(vdev);
	}

	count = vfio_default_config_write(vdev, pos, count, perm, offset, val);
	if (count < 0)
		return count;

	/*
	 * Save current memory/io enable bits in vconfig to allow for
	 * the test above next time.
	 */
	if (offset == PCI_COMMAND) {
		u16 mask = PCI_COMMAND_MEMORY | PCI_COMMAND_IO;

		*virt_cmd &= cpu_to_le16(~mask);
		*virt_cmd |= cpu_to_le16(new_cmd & mask);
	}

	/* Emulate INTx disable */
	if (offset >= PCI_COMMAND && offset <= PCI_COMMAND + 1) {
		bool virt_intx_disable;

		virt_intx_disable = !!(le16_to_cpu(*virt_cmd) &
				       PCI_COMMAND_INTX_DISABLE);

		if (virt_intx_disable && !vdev->virq_disabled) {
			vdev->virq_disabled = true;
			vfio_pci_intx_mask(vdev);
		} else if (!virt_intx_disable && vdev->virq_disabled) {
			vdev->virq_disabled = false;
			vfio_pci_intx_unmask(vdev);
		}
	}

	if (is_bar(offset))
		vdev->bardirty = true;

	return count;
}