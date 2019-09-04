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
struct i2c_client {int dummy; } ;
struct cht_int33fe_data {int /*<<< orphan*/  connections; scalar_t__ max17047; scalar_t__ fusb302; scalar_t__ pi3usb30532; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_connections_remove (int /*<<< orphan*/ ) ; 
 struct cht_int33fe_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_unregister_device (scalar_t__) ; 

__attribute__((used)) static int cht_int33fe_remove(struct i2c_client *i2c)
{
	struct cht_int33fe_data *data = i2c_get_clientdata(i2c);

	i2c_unregister_device(data->pi3usb30532);
	i2c_unregister_device(data->fusb302);
	if (data->max17047)
		i2c_unregister_device(data->max17047);

	device_connections_remove(data->connections);

	return 0;
}