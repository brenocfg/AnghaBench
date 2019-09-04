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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_START_FORCE ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_activate (struct irq_desc*) ; 
 int irq_startup (struct irq_desc*,int,int /*<<< orphan*/ ) ; 

int irq_activate_and_startup(struct irq_desc *desc, bool resend)
{
	if (WARN_ON(irq_activate(desc)))
		return 0;
	return irq_startup(desc, resend, IRQ_START_FORCE);
}