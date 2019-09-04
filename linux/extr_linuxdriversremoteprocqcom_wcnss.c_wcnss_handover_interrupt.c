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

__attribute__((used)) static irqreturn_t wcnss_handover_interrupt(int irq, void *dev)
{
	/*
	 * XXX: At this point we're supposed to release the resources that we
	 * have been holding on behalf of the WCNSS. Unfortunately this
	 * interrupt comes way before the other side seems to be done.
	 *
	 * So we're currently relying on the ready interrupt firing later then
	 * this and we just disable the resources at the end of wcnss_start().
	 */

	return IRQ_HANDLED;
}