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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct spmi_pmic_arb {TYPE_1__* ver_ops; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* irq_clear ) (struct spmi_pmic_arb*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QPNPINT_REG_LATCHED_CLR ; 
 int /*<<< orphan*/  hwirq_to_apid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwirq_to_irq (int /*<<< orphan*/ ) ; 
 struct spmi_pmic_arb* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  qpnpint_spmi_write (struct irq_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct spmi_pmic_arb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qpnpint_irq_ack(struct irq_data *d)
{
	struct spmi_pmic_arb *pmic_arb = irq_data_get_irq_chip_data(d);
	u8 irq = hwirq_to_irq(d->hwirq);
	u16 apid = hwirq_to_apid(d->hwirq);
	u8 data;

	writel_relaxed(BIT(irq), pmic_arb->ver_ops->irq_clear(pmic_arb, apid));

	data = BIT(irq);
	qpnpint_spmi_write(d, QPNPINT_REG_LATCHED_CLR, &data, 1);
}