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
struct xgene_msi_group {int msi_grp; struct xgene_msi* msi; } ;
struct xgene_msi {int /*<<< orphan*/  inner_domain; } ;
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;

/* Variables and functions */
 int IRQS_PER_IDX ; 
 int NR_HW_IRQS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 int ffs (int) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 int hwirq_to_canonical_hwirq (int) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct xgene_msi_group* irq_desc_get_handler_data (struct irq_desc*) ; 
 unsigned int irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int xgene_msi_int_read (struct xgene_msi*,int) ; 
 int xgene_msi_ir_read (struct xgene_msi*,int,int) ; 

__attribute__((used)) static void xgene_msi_isr(struct irq_desc *desc)
{
	struct irq_chip *chip = irq_desc_get_chip(desc);
	struct xgene_msi_group *msi_groups;
	struct xgene_msi *xgene_msi;
	unsigned int virq;
	int msir_index, msir_val, hw_irq;
	u32 intr_index, grp_select, msi_grp;

	chained_irq_enter(chip, desc);

	msi_groups = irq_desc_get_handler_data(desc);
	xgene_msi = msi_groups->msi;
	msi_grp = msi_groups->msi_grp;

	/*
	 * MSIINTn (n is 0..F) indicates if there is a pending MSI interrupt
	 * If bit x of this register is set (x is 0..7), one or more interupts
	 * corresponding to MSInIRx is set.
	 */
	grp_select = xgene_msi_int_read(xgene_msi, msi_grp);
	while (grp_select) {
		msir_index = ffs(grp_select) - 1;
		/*
		 * Calculate MSInIRx address to read to check for interrupts
		 * (refer to termination address and data assignment
		 * described in xgene_compose_msi_msg() )
		 */
		msir_val = xgene_msi_ir_read(xgene_msi, msi_grp, msir_index);
		while (msir_val) {
			intr_index = ffs(msir_val) - 1;
			/*
			 * Calculate MSI vector number (refer to the termination
			 * address and data assignment described in
			 * xgene_compose_msi_msg function)
			 */
			hw_irq = (((msir_index * IRQS_PER_IDX) + intr_index) *
				 NR_HW_IRQS) + msi_grp;
			/*
			 * As we have multiple hw_irq that maps to single MSI,
			 * always look up the virq using the hw_irq as seen from
			 * CPU0
			 */
			hw_irq = hwirq_to_canonical_hwirq(hw_irq);
			virq = irq_find_mapping(xgene_msi->inner_domain, hw_irq);
			WARN_ON(!virq);
			if (virq != 0)
				generic_handle_irq(virq);
			msir_val &= ~(1 << intr_index);
		}
		grp_select &= ~(1 << msir_index);

		if (!grp_select) {
			/*
			 * We handled all interrupts happened in this group,
			 * resample this group MSI_INTx register in case
			 * something else has been made pending in the meantime
			 */
			grp_select = xgene_msi_int_read(xgene_msi, msi_grp);
		}
	}

	chained_irq_exit(chip, desc);
}