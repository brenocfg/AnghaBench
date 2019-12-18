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
struct platform_device {int dummy; } ;
struct gpio_keys_platform_data {int /*<<< orphan*/  (* enable ) (int /*<<< orphan*/ ) ;} ;
struct gpio_keys_button_dev {int /*<<< orphan*/  dev; struct gpio_keys_platform_data* pdata; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int gpio_keys_button_probe (struct platform_device*,struct gpio_keys_button_dev**,int) ; 
 int /*<<< orphan*/  gpio_keys_polled_poll ; 
 int /*<<< orphan*/  gpio_keys_polled_queue_work (struct gpio_keys_button_dev*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpio_keys_polled_probe(struct platform_device *pdev)
{
	struct gpio_keys_platform_data *pdata;
	struct gpio_keys_button_dev *bdev;
	int ret;

	ret = gpio_keys_button_probe(pdev, &bdev, 1);

	if (ret)
		return ret;

	INIT_DELAYED_WORK(&bdev->work, gpio_keys_polled_poll);

	pdata = bdev->pdata;

	if (pdata->enable)
		pdata->enable(bdev->dev);

	gpio_keys_polled_queue_work(bdev);

	return ret;
}