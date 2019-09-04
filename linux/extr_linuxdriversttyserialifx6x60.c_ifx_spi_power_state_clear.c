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
struct ifx_spi_device {int power_status; int /*<<< orphan*/  power_lock; TYPE_1__* spi_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
ifx_spi_power_state_clear(struct ifx_spi_device *ifx_dev, unsigned char val)
{
	unsigned long flags;

	spin_lock_irqsave(&ifx_dev->power_lock, flags);

	if (ifx_dev->power_status) {
		ifx_dev->power_status &= ~val;
		if (!ifx_dev->power_status)
			pm_runtime_put(&ifx_dev->spi_dev->dev);
	}

	spin_unlock_irqrestore(&ifx_dev->power_lock, flags);
}