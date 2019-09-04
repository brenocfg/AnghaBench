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
struct platform_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static irqreturn_t cdns_wdt_irq_handler(int irq, void *dev_id)
{
	struct platform_device *pdev = dev_id;

	dev_info(&pdev->dev,
		 "Watchdog timed out. Internal reset not enabled\n");

	return IRQ_HANDLED;
}