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
struct pcs_soc_data {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ pcs_irq_handle (struct pcs_soc_data*) ; 

__attribute__((used)) static irqreturn_t pcs_irq_handler(int irq, void *d)
{
	struct pcs_soc_data *pcs_soc = d;

	return pcs_irq_handle(pcs_soc) ? IRQ_HANDLED : IRQ_NONE;
}