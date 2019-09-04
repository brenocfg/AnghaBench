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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct abb5zes3_rtc_data {scalar_t__ irq; } ;

/* Variables and functions */
 struct abb5zes3_rtc_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int abb5zes3_remove(struct i2c_client *client)
{
	struct abb5zes3_rtc_data *rtc_data = dev_get_drvdata(&client->dev);

	if (rtc_data->irq > 0)
		device_init_wakeup(&client->dev, false);

	return 0;
}