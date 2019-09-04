#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tegra_io_pad_soc {int dpd; } ;
typedef  enum tegra_io_pad { ____Placeholder_tegra_io_pad } tegra_io_pad ;
struct TYPE_7__ {scalar_t__ clk; TYPE_2__* soc; } ;
struct TYPE_6__ {TYPE_1__* regs; } ;
struct TYPE_5__ {unsigned long dpd_status; unsigned long dpd_req; unsigned long dpd2_status; unsigned long dpd2_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 unsigned long DIV_ROUND_UP (int,unsigned long) ; 
 int /*<<< orphan*/  DPD_SAMPLE ; 
 unsigned long DPD_SAMPLE_ENABLE ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  SEL_DPD_TIM ; 
 int UINT_MAX ; 
 unsigned long clk_get_rate (scalar_t__) ; 
 TYPE_3__* pmc ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 struct tegra_io_pad_soc* tegra_io_pad_find (TYPE_3__*,int) ; 
 int /*<<< orphan*/  tegra_pmc_writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_io_pad_prepare(enum tegra_io_pad id, unsigned long *request,
				unsigned long *status, u32 *mask)
{
	const struct tegra_io_pad_soc *pad;
	unsigned long rate, value;

	pad = tegra_io_pad_find(pmc, id);
	if (!pad) {
		pr_err("invalid I/O pad ID %u\n", id);
		return -ENOENT;
	}

	if (pad->dpd == UINT_MAX)
		return -ENOTSUPP;

	*mask = BIT(pad->dpd % 32);

	if (pad->dpd < 32) {
		*status = pmc->soc->regs->dpd_status;
		*request = pmc->soc->regs->dpd_req;
	} else {
		*status = pmc->soc->regs->dpd2_status;
		*request = pmc->soc->regs->dpd2_req;
	}

	if (pmc->clk) {
		rate = clk_get_rate(pmc->clk);
		if (!rate) {
			pr_err("failed to get clock rate\n");
			return -ENODEV;
		}

		tegra_pmc_writel(DPD_SAMPLE_ENABLE, DPD_SAMPLE);

		/* must be at least 200 ns, in APB (PCLK) clock cycles */
		value = DIV_ROUND_UP(1000000000, rate);
		value = DIV_ROUND_UP(200, value);
		tegra_pmc_writel(value, SEL_DPD_TIM);
	}

	return 0;
}