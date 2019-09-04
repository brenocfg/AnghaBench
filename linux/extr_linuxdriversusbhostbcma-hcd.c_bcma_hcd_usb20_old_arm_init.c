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
struct device {int /*<<< orphan*/  of_node; } ;
struct bcma_hcd_device {struct bcma_device* core; } ;
struct TYPE_2__ {int rev; } ;
struct bcma_device {int /*<<< orphan*/  bus; TYPE_1__ id; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CC_PMU_CTL ; 
 int /*<<< orphan*/  BCMA_CC_PMU_CTL_PLL_UPD ; 
 int BCMA_CC_PMU_PLLCTL_ADDR ; 
 int BCMA_CC_PMU_PLLCTL_DATA ; 
 int BCMA_CLKCTLST ; 
 int BCMA_CLKCTLST_FORCEHT ; 
 int BCMA_CLKCTLST_HQCLKREQ ; 
 int /*<<< orphan*/  BCMA_CORE_PMU ; 
 int /*<<< orphan*/  BCMA_IOCTL ; 
 int BCMA_IOCTL_CLK ; 
 int BCMA_IOCTL_FGC ; 
 int /*<<< orphan*/  BCMA_RESET_CTL ; 
 int BCMA_RESET_CTL_RESET ; 
 int ENOENT ; 
 int USB_BCMA_CLKCTLST_USB_CLK_REQ ; 
 int /*<<< orphan*/  bcma_awrite32 (struct bcma_device*,int /*<<< orphan*/ ,int) ; 
 struct bcma_device* bcma_find_core (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_set32 (struct bcma_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_write32 (struct bcma_device*,int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  of_platform_default_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int bcma_hcd_usb20_old_arm_init(struct bcma_hcd_device *usb_dev)
{
	struct bcma_device *core = usb_dev->core;
	struct device *dev = &core->dev;
	struct bcma_device *pmu_core;

	usleep_range(10000, 20000);
	if (core->id.rev < 5)
		return 0;

	pmu_core = bcma_find_core(core->bus, BCMA_CORE_PMU);
	if (!pmu_core) {
		dev_err(dev, "Could not find PMU core\n");
		return -ENOENT;
	}

	/* Take USB core out of reset */
	bcma_awrite32(core, BCMA_IOCTL, BCMA_IOCTL_CLK | BCMA_IOCTL_FGC);
	usleep_range(100, 200);
	bcma_awrite32(core, BCMA_RESET_CTL, BCMA_RESET_CTL_RESET);
	usleep_range(100, 200);
	bcma_awrite32(core, BCMA_RESET_CTL, 0);
	usleep_range(100, 200);
	bcma_awrite32(core, BCMA_IOCTL, BCMA_IOCTL_CLK);
	usleep_range(100, 200);

	/* Enable Misc PLL */
	bcma_write32(core, BCMA_CLKCTLST, BCMA_CLKCTLST_FORCEHT |
					  BCMA_CLKCTLST_HQCLKREQ |
					  USB_BCMA_CLKCTLST_USB_CLK_REQ);
	usleep_range(100, 200);

	bcma_write32(core, 0x510, 0xc7f85000);
	bcma_write32(core, 0x510, 0xc7f85003);
	usleep_range(300, 600);

	/* Program USB PHY PLL parameters */
	bcma_write32(pmu_core, BCMA_CC_PMU_PLLCTL_ADDR, 0x6);
	bcma_write32(pmu_core, BCMA_CC_PMU_PLLCTL_DATA, 0x005360c1);
	usleep_range(100, 200);
	bcma_write32(pmu_core, BCMA_CC_PMU_PLLCTL_ADDR, 0x7);
	bcma_write32(pmu_core, BCMA_CC_PMU_PLLCTL_DATA, 0x0);
	usleep_range(100, 200);
	bcma_set32(pmu_core, BCMA_CC_PMU_CTL, BCMA_CC_PMU_CTL_PLL_UPD);
	usleep_range(100, 200);

	bcma_write32(core, 0x510, 0x7f8d007);
	udelay(1000);

	/* Take controller out of reset */
	bcma_write32(core, 0x200, 0x4ff);
	usleep_range(25, 50);
	bcma_write32(core, 0x200, 0x6ff);
	usleep_range(25, 50);
	bcma_write32(core, 0x200, 0x7ff);
	usleep_range(25, 50);

	of_platform_default_populate(dev->of_node, NULL, dev);

	return 0;
}