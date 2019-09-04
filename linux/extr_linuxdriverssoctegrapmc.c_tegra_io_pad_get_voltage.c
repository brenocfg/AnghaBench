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
struct tegra_io_pad_soc {scalar_t__ voltage; } ;
typedef  enum tegra_io_pad { ____Placeholder_tegra_io_pad } tegra_io_pad ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int ENOENT ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  PMC_PWR_DET_VALUE ; 
 int TEGRA_IO_PAD_1800000UV ; 
 int TEGRA_IO_PAD_3300000UV ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  pmc ; 
 struct tegra_io_pad_soc* tegra_io_pad_find (int /*<<< orphan*/ ,int) ; 
 int tegra_pmc_readl (int /*<<< orphan*/ ) ; 

int tegra_io_pad_get_voltage(enum tegra_io_pad id)
{
	const struct tegra_io_pad_soc *pad;
	u32 value;

	pad = tegra_io_pad_find(pmc, id);
	if (!pad)
		return -ENOENT;

	if (pad->voltage == UINT_MAX)
		return -ENOTSUPP;

	value = tegra_pmc_readl(PMC_PWR_DET_VALUE);

	if ((value & BIT(pad->voltage)) == 0)
		return TEGRA_IO_PAD_1800000UV;

	return TEGRA_IO_PAD_3300000UV;
}