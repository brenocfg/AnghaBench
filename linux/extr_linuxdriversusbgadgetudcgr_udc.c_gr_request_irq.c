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
struct gr_udc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gr_udc*) ; 
 int /*<<< orphan*/  driver_name ; 
 int /*<<< orphan*/  gr_irq ; 
 int /*<<< orphan*/  gr_irq_handler ; 

__attribute__((used)) static int gr_request_irq(struct gr_udc *dev, int irq)
{
	return devm_request_threaded_irq(dev->dev, irq, gr_irq, gr_irq_handler,
					 IRQF_SHARED, driver_name, dev);
}