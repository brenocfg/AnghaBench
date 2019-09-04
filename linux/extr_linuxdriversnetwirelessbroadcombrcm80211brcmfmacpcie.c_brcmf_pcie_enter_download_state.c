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
struct brcmf_pciedev_info {TYPE_1__* ci; } ;
struct TYPE_2__ {scalar_t__ chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CORE_ARM_CR4 ; 
 int /*<<< orphan*/  BRCMF_PCIE_ARMCR4REG_BANKIDX ; 
 int /*<<< orphan*/  BRCMF_PCIE_ARMCR4REG_BANKPDA ; 
 scalar_t__ BRCM_CC_43602_CHIP_ID ; 
 int /*<<< orphan*/  brcmf_pcie_select_core (struct brcmf_pciedev_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_pcie_write_reg32 (struct brcmf_pciedev_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int brcmf_pcie_enter_download_state(struct brcmf_pciedev_info *devinfo)
{
	if (devinfo->ci->chip == BRCM_CC_43602_CHIP_ID) {
		brcmf_pcie_select_core(devinfo, BCMA_CORE_ARM_CR4);
		brcmf_pcie_write_reg32(devinfo, BRCMF_PCIE_ARMCR4REG_BANKIDX,
				       5);
		brcmf_pcie_write_reg32(devinfo, BRCMF_PCIE_ARMCR4REG_BANKPDA,
				       0);
		brcmf_pcie_write_reg32(devinfo, BRCMF_PCIE_ARMCR4REG_BANKIDX,
				       7);
		brcmf_pcie_write_reg32(devinfo, BRCMF_PCIE_ARMCR4REG_BANKPDA,
				       0);
	}
	return 0;
}