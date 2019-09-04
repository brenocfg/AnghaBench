#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct brcmf_pciedev_info {TYPE_1__* ci; } ;
struct brcmf_core {int dummy; } ;
struct TYPE_3__ {scalar_t__ chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CORE_INTERNAL_MEM ; 
 scalar_t__ BRCM_CC_43602_CHIP_ID ; 
 int EINVAL ; 
 struct brcmf_core* brcmf_chip_get_core (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_chip_resetcore (struct brcmf_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_chip_set_active (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmf_pcie_exit_download_state(struct brcmf_pciedev_info *devinfo,
					  u32 resetintr)
{
	struct brcmf_core *core;

	if (devinfo->ci->chip == BRCM_CC_43602_CHIP_ID) {
		core = brcmf_chip_get_core(devinfo->ci, BCMA_CORE_INTERNAL_MEM);
		brcmf_chip_resetcore(core, 0, 0, 0);
	}

	if (!brcmf_chip_set_active(devinfo->ci, resetintr))
		return -EINVAL;
	return 0;
}