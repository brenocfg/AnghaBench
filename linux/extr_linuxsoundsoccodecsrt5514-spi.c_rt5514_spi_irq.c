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
struct rt5514_dsp {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  rt5514_schedule_copy (struct rt5514_dsp*) ; 

__attribute__((used)) static irqreturn_t rt5514_spi_irq(int irq, void *data)
{
	struct rt5514_dsp *rt5514_dsp = data;

	rt5514_schedule_copy(rt5514_dsp);

	return IRQ_HANDLED;
}