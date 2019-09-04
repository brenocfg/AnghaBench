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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 int /*<<< orphan*/  napi_schedule (void*) ; 

__attribute__((used)) static irqreturn_t cvm_oct_do_interrupt(int irq, void *napi_id)
{
	/* Disable the IRQ and start napi_poll. */
	disable_irq_nosync(irq);
	napi_schedule(napi_id);

	return IRQ_HANDLED;
}