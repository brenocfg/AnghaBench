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
typedef  int /*<<< orphan*/  u8 ;
struct gb_gpio_irq_unmask_request {int /*<<< orphan*/  which; } ;
struct gb_gpio_controller {int /*<<< orphan*/  connection; TYPE_1__* gbphy_dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  request ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_GPIO_TYPE_IRQ_UNMASK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_gpio_irq_unmask_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _gb_gpio_irq_unmask(struct gb_gpio_controller *ggc, u8 hwirq)
{
	struct device *dev = &ggc->gbphy_dev->dev;
	struct gb_gpio_irq_unmask_request request;
	int ret;

	request.which = hwirq;
	ret = gb_operation_sync(ggc->connection,
				GB_GPIO_TYPE_IRQ_UNMASK,
				&request, sizeof(request), NULL, 0);
	if (ret)
		dev_err(dev, "failed to unmask irq: %d\n", ret);
}