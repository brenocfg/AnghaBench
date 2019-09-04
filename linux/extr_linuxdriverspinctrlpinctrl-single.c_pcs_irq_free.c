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
struct pcs_soc_data {scalar_t__ irq; } ;
struct pcs_device {scalar_t__ domain; struct pcs_soc_data socdata; } ;

/* Variables and functions */
 scalar_t__ PCS_QUIRK_HAS_SHARED_IRQ ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct pcs_soc_data*) ; 
 int /*<<< orphan*/  irq_domain_remove (scalar_t__) ; 
 int /*<<< orphan*/  irq_set_chained_handler (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pcs_irq_free(struct pcs_device *pcs)
{
	struct pcs_soc_data *pcs_soc = &pcs->socdata;

	if (pcs_soc->irq < 0)
		return;

	if (pcs->domain)
		irq_domain_remove(pcs->domain);

	if (PCS_QUIRK_HAS_SHARED_IRQ)
		free_irq(pcs_soc->irq, pcs_soc);
	else
		irq_set_chained_handler(pcs_soc->irq, NULL);
}