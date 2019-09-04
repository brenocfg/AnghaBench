#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct vlynq_device {TYPE_1__* local; int /*<<< orphan*/  dev; } ;
struct irq_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct vlynq_device* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vlynq_local_ack(struct irq_data *d)
{
	struct vlynq_device *dev = irq_data_get_irq_chip_data(d);
	u32 status = readl(&dev->local->status);

	pr_debug("%s: local status: 0x%08x\n",
		       dev_name(&dev->dev), status);
	writel(status, &dev->local->status);
}