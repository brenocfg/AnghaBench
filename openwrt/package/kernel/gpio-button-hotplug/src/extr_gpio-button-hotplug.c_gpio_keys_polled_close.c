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
struct gpio_keys_platform_data {int /*<<< orphan*/  (* disable ) (int /*<<< orphan*/ ) ;} ;
struct gpio_keys_button_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  work; struct gpio_keys_platform_data* pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpio_keys_polled_close(struct gpio_keys_button_dev *bdev)
{
	struct gpio_keys_platform_data *pdata = bdev->pdata;

	cancel_delayed_work_sync(&bdev->work);

	if (pdata->disable)
		pdata->disable(bdev->dev);
}