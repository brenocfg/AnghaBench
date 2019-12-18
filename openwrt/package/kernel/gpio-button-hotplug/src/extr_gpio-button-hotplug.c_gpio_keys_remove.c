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
struct gpio_keys_button_dev {scalar_t__ polled; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_keys_irq_close (struct gpio_keys_button_dev*) ; 
 int /*<<< orphan*/  gpio_keys_polled_close (struct gpio_keys_button_dev*) ; 
 struct gpio_keys_button_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gpio_keys_remove(struct platform_device *pdev)
{
	struct gpio_keys_button_dev *bdev = platform_get_drvdata(pdev);

	platform_set_drvdata(pdev, NULL);

	if (bdev->polled)
		gpio_keys_polled_close(bdev);
	else
		gpio_keys_irq_close(bdev);

	return 0;
}