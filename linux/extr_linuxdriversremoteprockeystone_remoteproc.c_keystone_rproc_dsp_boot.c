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
struct keystone_rproc {int /*<<< orphan*/  reset; int /*<<< orphan*/  dev; int /*<<< orphan*/  boot_offset; int /*<<< orphan*/  dev_ctrl; } ;

/* Variables and functions */
 int EINVAL ; 
 int SZ_1K ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int keystone_rproc_dsp_boot(struct keystone_rproc *ksproc, u32 boot_addr)
{
	int ret;

	if (boot_addr & (SZ_1K - 1)) {
		dev_err(ksproc->dev, "invalid boot address 0x%x, must be aligned on a 1KB boundary\n",
			boot_addr);
		return -EINVAL;
	}

	ret = regmap_write(ksproc->dev_ctrl, ksproc->boot_offset, boot_addr);
	if (ret) {
		dev_err(ksproc->dev, "regmap_write of boot address failed, status = %d\n",
			ret);
		return ret;
	}

	reset_control_deassert(ksproc->reset);

	return 0;
}