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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct spmi_pmic_arb {struct pmic_arb_ver_ops* ver_ops; } ;
struct pmic_arb_ver_ops {int /*<<< orphan*/  (* acc_enable ) (struct spmi_pmic_arb*,int /*<<< orphan*/ ) ;} ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  QPNPINT_REG_EN_SET ; 
 int /*<<< orphan*/  QPNPINT_REG_LATCHED_CLR ; 
 int /*<<< orphan*/  SPMI_PIC_ACC_ENABLE_BIT ; 
 int /*<<< orphan*/  hwirq_to_apid (int /*<<< orphan*/ ) ; 
 int hwirq_to_irq (int /*<<< orphan*/ ) ; 
 struct spmi_pmic_arb* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  qpnpint_spmi_read (struct irq_data*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  qpnpint_spmi_write (struct irq_data*,int /*<<< orphan*/ ,int**,int) ; 
 int /*<<< orphan*/  stub1 (struct spmi_pmic_arb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qpnpint_irq_unmask(struct irq_data *d)
{
	struct spmi_pmic_arb *pmic_arb = irq_data_get_irq_chip_data(d);
	const struct pmic_arb_ver_ops *ver_ops = pmic_arb->ver_ops;
	u8 irq = hwirq_to_irq(d->hwirq);
	u16 apid = hwirq_to_apid(d->hwirq);
	u8 buf[2];

	writel_relaxed(SPMI_PIC_ACC_ENABLE_BIT,
			ver_ops->acc_enable(pmic_arb, apid));

	qpnpint_spmi_read(d, QPNPINT_REG_EN_SET, &buf[0], 1);
	if (!(buf[0] & BIT(irq))) {
		/*
		 * Since the interrupt is currently disabled, write to both the
		 * LATCHED_CLR and EN_SET registers so that a spurious interrupt
		 * cannot be triggered when the interrupt is enabled
		 */
		buf[0] = BIT(irq);
		buf[1] = BIT(irq);
		qpnpint_spmi_write(d, QPNPINT_REG_LATCHED_CLR, &buf, 2);
	}
}