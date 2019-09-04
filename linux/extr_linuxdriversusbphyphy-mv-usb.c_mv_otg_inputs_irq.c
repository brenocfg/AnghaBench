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
struct mv_otg {int /*<<< orphan*/  active; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  mv_otg_enable (struct mv_otg*) ; 
 int /*<<< orphan*/  mv_otg_init_irq (struct mv_otg*) ; 
 int /*<<< orphan*/  mv_otg_run_state_machine (struct mv_otg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t mv_otg_inputs_irq(int irq, void *dev)
{
	struct mv_otg *mvotg = dev;

	/* The clock may disabled at this time */
	if (!mvotg->active) {
		mv_otg_enable(mvotg);
		mv_otg_init_irq(mvotg);
	}

	mv_otg_run_state_machine(mvotg, 0);

	return IRQ_HANDLED;
}