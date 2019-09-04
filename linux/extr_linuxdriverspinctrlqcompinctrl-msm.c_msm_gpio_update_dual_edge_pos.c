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
struct msm_pingroup {scalar_t__ intr_status_reg; int /*<<< orphan*/  in_bit; scalar_t__ io_reg; scalar_t__ intr_cfg_reg; int /*<<< orphan*/  intr_polarity_bit; } ;
struct msm_pinctrl {int /*<<< orphan*/  dev; scalar_t__ regs; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void msm_gpio_update_dual_edge_pos(struct msm_pinctrl *pctrl,
					  const struct msm_pingroup *g,
					  struct irq_data *d)
{
	int loop_limit = 100;
	unsigned val, val2, intstat;
	unsigned pol;

	do {
		val = readl(pctrl->regs + g->io_reg) & BIT(g->in_bit);

		pol = readl(pctrl->regs + g->intr_cfg_reg);
		pol ^= BIT(g->intr_polarity_bit);
		writel(pol, pctrl->regs + g->intr_cfg_reg);

		val2 = readl(pctrl->regs + g->io_reg) & BIT(g->in_bit);
		intstat = readl(pctrl->regs + g->intr_status_reg);
		if (intstat || (val == val2))
			return;
	} while (loop_limit-- > 0);
	dev_err(pctrl->dev, "dual-edge irq failed to stabilize, %#08x != %#08x\n",
		val, val2);
}