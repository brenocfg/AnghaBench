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
struct vme_bridge {int /*<<< orphan*/  parent; struct tsi148_driver* driver_priv; } ;
struct tsi148_driver {int /*<<< orphan*/  flush_image; scalar_t__ base; int /*<<< orphan*/  crcsr_bus; int /*<<< orphan*/  crcsr_kernel; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ TSI148_CBAR ; 
 int TSI148_CRCSR_CBAR_M ; 
 scalar_t__ TSI148_LCSR_CRAT ; 
 int TSI148_LCSR_CRAT_EN ; 
 scalar_t__ TSI148_LCSR_CROL ; 
 scalar_t__ TSI148_LCSR_CROU ; 
 int /*<<< orphan*/  VME_CRCSR ; 
 int /*<<< orphan*/  VME_CRCSR_BUF_SIZE ; 
 int /*<<< orphan*/  VME_D16 ; 
 int /*<<< orphan*/  VME_SCT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ err_chk ; 
 int ioread32be (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32be (int,scalar_t__) ; 
 int /*<<< orphan*/  pci_zalloc_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_split (int /*<<< orphan*/ ,int*,int*) ; 
 int tsi148_master_set (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tsi148_slot_get (struct vme_bridge*) ; 

__attribute__((used)) static int tsi148_crcsr_init(struct vme_bridge *tsi148_bridge,
	struct pci_dev *pdev)
{
	u32 cbar, crat, vstat;
	u32 crcsr_bus_high, crcsr_bus_low;
	int retval;
	struct tsi148_driver *bridge;

	bridge = tsi148_bridge->driver_priv;

	/* Allocate mem for CR/CSR image */
	bridge->crcsr_kernel = pci_zalloc_consistent(pdev, VME_CRCSR_BUF_SIZE,
						     &bridge->crcsr_bus);
	if (!bridge->crcsr_kernel) {
		dev_err(tsi148_bridge->parent, "Failed to allocate memory for "
			"CR/CSR image\n");
		return -ENOMEM;
	}

	reg_split(bridge->crcsr_bus, &crcsr_bus_high, &crcsr_bus_low);

	iowrite32be(crcsr_bus_high, bridge->base + TSI148_LCSR_CROU);
	iowrite32be(crcsr_bus_low, bridge->base + TSI148_LCSR_CROL);

	/* Ensure that the CR/CSR is configured at the correct offset */
	cbar = ioread32be(bridge->base + TSI148_CBAR);
	cbar = (cbar & TSI148_CRCSR_CBAR_M)>>3;

	vstat = tsi148_slot_get(tsi148_bridge);

	if (cbar != vstat) {
		cbar = vstat;
		dev_info(tsi148_bridge->parent, "Setting CR/CSR offset\n");
		iowrite32be(cbar<<3, bridge->base + TSI148_CBAR);
	}
	dev_info(tsi148_bridge->parent, "CR/CSR Offset: %d\n", cbar);

	crat = ioread32be(bridge->base + TSI148_LCSR_CRAT);
	if (crat & TSI148_LCSR_CRAT_EN)
		dev_info(tsi148_bridge->parent, "CR/CSR already enabled\n");
	else {
		dev_info(tsi148_bridge->parent, "Enabling CR/CSR space\n");
		iowrite32be(crat | TSI148_LCSR_CRAT_EN,
			bridge->base + TSI148_LCSR_CRAT);
	}

	/* If we want flushed, error-checked writes, set up a window
	 * over the CR/CSR registers. We read from here to safely flush
	 * through VME writes.
	 */
	if (err_chk) {
		retval = tsi148_master_set(bridge->flush_image, 1,
			(vstat * 0x80000), 0x80000, VME_CRCSR, VME_SCT,
			VME_D16);
		if (retval)
			dev_err(tsi148_bridge->parent, "Configuring flush image"
				" failed\n");
	}

	return 0;

}