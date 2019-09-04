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
struct iio_dev {struct device dev; } ;

/* Variables and functions */
 scalar_t__ ADE7854_STARTUP_DELAY ; 
 int /*<<< orphan*/  ade7854_reset (struct device*) ; 
 int ade7854_set_irq (struct device*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  usleep_range (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ade7854_initial_setup(struct iio_dev *indio_dev)
{
	int ret;
	struct device *dev = &indio_dev->dev;

	/* Disable IRQ */
	ret = ade7854_set_irq(dev, false);
	if (ret) {
		dev_err(dev, "disable irq failed");
		goto err_ret;
	}

	ade7854_reset(dev);
	usleep_range(ADE7854_STARTUP_DELAY, ADE7854_STARTUP_DELAY + 100);

err_ret:
	return ret;
}