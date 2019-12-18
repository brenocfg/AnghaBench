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
struct rt5640_priv {int /*<<< orphan*/  jack_work; scalar_t__ jack; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_long_wq ; 

__attribute__((used)) static irqreturn_t rt5640_irq(int irq, void *data)
{
	struct rt5640_priv *rt5640 = data;

	if (rt5640->jack)
		queue_work(system_long_wq, &rt5640->jack_work);

	return IRQ_HANDLED;
}