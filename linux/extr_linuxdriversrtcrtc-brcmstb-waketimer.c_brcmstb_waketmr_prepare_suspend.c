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
struct device {int dummy; } ;
struct brcmstb_waketmr {int /*<<< orphan*/  irq; struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ device_may_wakeup (struct device*) ; 
 int enable_irq_wake (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmstb_waketmr_prepare_suspend(struct brcmstb_waketmr *timer)
{
	struct device *dev = timer->dev;
	int ret = 0;

	if (device_may_wakeup(dev)) {
		ret = enable_irq_wake(timer->irq);
		if (ret) {
			dev_err(dev, "failed to enable wake-up interrupt\n");
			return ret;
		}
	}

	return ret;
}