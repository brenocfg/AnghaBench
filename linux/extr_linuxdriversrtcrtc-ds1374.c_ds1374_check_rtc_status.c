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

/* Variables and functions */
 int /*<<< orphan*/  DS1374_REG_CR ; 
 int DS1374_REG_CR_AIE ; 
 int DS1374_REG_CR_WACE ; 
 int /*<<< orphan*/  DS1374_REG_SR ; 
 int DS1374_REG_SR_AF ; 
 int DS1374_REG_SR_OSF ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ds1374_check_rtc_status(struct i2c_client *client)
{
	int ret = 0;
	int control, stat;

	stat = i2c_smbus_read_byte_data(client, DS1374_REG_SR);
	if (stat < 0)
		return stat;

	if (stat & DS1374_REG_SR_OSF)
		dev_warn(&client->dev,
			 "oscillator discontinuity flagged, time unreliable\n");

	stat &= ~(DS1374_REG_SR_OSF | DS1374_REG_SR_AF);

	ret = i2c_smbus_write_byte_data(client, DS1374_REG_SR, stat);
	if (ret < 0)
		return ret;

	/* If the alarm is pending, clear it before requesting
	 * the interrupt, so an interrupt event isn't reported
	 * before everything is initialized.
	 */

	control = i2c_smbus_read_byte_data(client, DS1374_REG_CR);
	if (control < 0)
		return control;

	control &= ~(DS1374_REG_CR_WACE | DS1374_REG_CR_AIE);
	return i2c_smbus_write_byte_data(client, DS1374_REG_CR, control);
}