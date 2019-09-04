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
struct smo8800_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static irqreturn_t smo8800_interrupt_thread(int irq, void *data)
{
	struct smo8800_device *smo8800 = data;

	dev_info(smo8800->dev, "detected free fall\n");
	return IRQ_HANDLED;
}