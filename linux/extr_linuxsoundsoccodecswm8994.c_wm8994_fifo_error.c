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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static irqreturn_t wm8994_fifo_error(int irq, void *data)
{
	struct snd_soc_component *component = data;

	dev_err(component->dev, "FIFO error\n");

	return IRQ_HANDLED;
}