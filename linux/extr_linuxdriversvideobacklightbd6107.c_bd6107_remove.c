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
struct i2c_client {int dummy; } ;
struct TYPE_2__ {scalar_t__ brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 struct backlight_device* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int bd6107_remove(struct i2c_client *client)
{
	struct backlight_device *backlight = i2c_get_clientdata(client);

	backlight->props.brightness = 0;
	backlight_update_status(backlight);

	return 0;
}