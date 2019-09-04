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
typedef  int u8 ;
struct spmi_pmic_arb {TYPE_1__* spmic; } ;
struct irq_data {int /*<<< orphan*/  irq; int /*<<< orphan*/  hwirq; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPMI_CMD_EXT_READL ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int hwirq_to_per (int /*<<< orphan*/ ) ; 
 int hwirq_to_sid (int /*<<< orphan*/ ) ; 
 struct spmi_pmic_arb* irq_data_get_irq_chip_data (struct irq_data*) ; 
 scalar_t__ pmic_arb_read_cmd (TYPE_1__*,int /*<<< orphan*/ ,int,int,void*,size_t) ; 

__attribute__((used)) static void qpnpint_spmi_read(struct irq_data *d, u8 reg, void *buf, size_t len)
{
	struct spmi_pmic_arb *pmic_arb = irq_data_get_irq_chip_data(d);
	u8 sid = hwirq_to_sid(d->hwirq);
	u8 per = hwirq_to_per(d->hwirq);

	if (pmic_arb_read_cmd(pmic_arb->spmic, SPMI_CMD_EXT_READL, sid,
			      (per << 8) + reg, buf, len))
		dev_err_ratelimited(&pmic_arb->spmic->dev, "failed irqchip transaction on %x\n",
				    d->irq);
}