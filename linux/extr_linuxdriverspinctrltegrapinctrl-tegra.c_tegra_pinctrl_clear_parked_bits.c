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
typedef  int u32 ;
struct tegra_pmx {TYPE_1__* soc; } ;
struct tegra_pingroup {int parked_bit; int /*<<< orphan*/  mux_reg; int /*<<< orphan*/  mux_bank; } ;
struct TYPE_2__ {int ngroups; struct tegra_pingroup* groups; } ;

/* Variables and functions */
 int pmx_readl (struct tegra_pmx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmx_writel (struct tegra_pmx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_pinctrl_clear_parked_bits(struct tegra_pmx *pmx)
{
	int i = 0;
	const struct tegra_pingroup *g;
	u32 val;

	for (i = 0; i < pmx->soc->ngroups; ++i) {
		g = &pmx->soc->groups[i];
		if (g->parked_bit >= 0) {
			val = pmx_readl(pmx, g->mux_bank, g->mux_reg);
			val &= ~(1 << g->parked_bit);
			pmx_writel(pmx, val, g->mux_bank, g->mux_reg);
		}
	}
}