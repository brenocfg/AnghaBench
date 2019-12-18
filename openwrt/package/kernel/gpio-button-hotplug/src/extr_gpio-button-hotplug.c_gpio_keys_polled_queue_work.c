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
struct gpio_keys_platform_data {int /*<<< orphan*/  poll_interval; } ;
struct gpio_keys_button_dev {int /*<<< orphan*/  work; struct gpio_keys_platform_data* pdata; } ;

/* Variables and functions */
 unsigned long HZ ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 unsigned long round_jiffies_relative (unsigned long) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void gpio_keys_polled_queue_work(struct gpio_keys_button_dev *bdev)
{
	struct gpio_keys_platform_data *pdata = bdev->pdata;
	unsigned long delay = msecs_to_jiffies(pdata->poll_interval);

	if (delay >= HZ)
		delay = round_jiffies_relative(delay);
	schedule_delayed_work(&bdev->work, delay);
}