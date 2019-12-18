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
struct irq_sim_irq_ctx {int enabled; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 struct irq_sim_irq_ctx* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static void irq_sim_irqunmask(struct irq_data *data)
{
	struct irq_sim_irq_ctx *irq_ctx = irq_data_get_irq_chip_data(data);

	irq_ctx->enabled = true;
}