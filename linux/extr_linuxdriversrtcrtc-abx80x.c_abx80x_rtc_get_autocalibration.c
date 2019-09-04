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
struct device {int dummy; } ;

/* Variables and functions */
 int ABX8XX_OSC_ACAL_1024 ; 
 int ABX8XX_OSC_ACAL_512 ; 
 int /*<<< orphan*/  ABX8XX_REG_OSC ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int abx80x_rtc_get_autocalibration(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	int flags = 0, autocalibration;

	flags =  i2c_smbus_read_byte_data(client, ABX8XX_REG_OSC);
	if (flags < 0)
		return flags;

	if (flags & ABX8XX_OSC_ACAL_512)
		autocalibration = 512;
	else if (flags & ABX8XX_OSC_ACAL_1024)
		autocalibration = 1024;
	else
		autocalibration = 0;

	return autocalibration;
}