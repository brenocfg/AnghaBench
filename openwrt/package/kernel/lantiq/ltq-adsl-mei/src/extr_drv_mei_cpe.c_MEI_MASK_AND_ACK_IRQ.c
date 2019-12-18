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
struct irq_data {int hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ltq_mask_and_ack_irq (struct irq_data*) ; 

__attribute__((used)) static void inline MEI_MASK_AND_ACK_IRQ(int x)
{
	struct irq_data d;
	d.hwirq = x;
	ltq_mask_and_ack_irq(&d);
}