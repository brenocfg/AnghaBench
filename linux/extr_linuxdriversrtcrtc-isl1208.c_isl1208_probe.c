#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct rtc_device {int /*<<< orphan*/  dev; int /*<<< orphan*/ * ops; } ;
struct i2c_device_id {scalar_t__ driver_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; struct device_node* of_node; } ;
struct i2c_client {int irq; TYPE_1__ dev; int /*<<< orphan*/  adapter; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int ISL1208_REG_SR_RTCF ; 
 int /*<<< orphan*/  ISL1219_REG_EV ; 
 int ISL1219_REG_EV_EVEN ; 
 int ISL1219_REG_EV_EVIENB ; 
 scalar_t__ IS_ERR (struct rtc_device*) ; 
 int PTR_ERR (struct rtc_device*) ; 
 scalar_t__ TYPE_ISL1219 ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct i2c_client*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 struct rtc_device* devm_rtc_allocate_device (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rtc_device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int isl1208_i2c_get_sr (struct i2c_client*) ; 
 scalar_t__ isl1208_i2c_validate_client (struct i2c_client*) ; 
 int /*<<< orphan*/  isl1208_rtc_ops ; 
 int /*<<< orphan*/  isl1208_rtc_sysfs_files ; 
 int isl1208_setup_irq (struct i2c_client*,int) ; 
 int /*<<< orphan*/  isl1219_rtc_sysfs_files ; 
 int of_irq_get_byname (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 int rtc_add_group (struct rtc_device*,int /*<<< orphan*/ *) ; 
 int rtc_register_device (struct rtc_device*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
isl1208_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int rc = 0;
	struct rtc_device *rtc;
	int evdet_irq = -1;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		return -ENODEV;

	if (isl1208_i2c_validate_client(client) < 0)
		return -ENODEV;

	rtc = devm_rtc_allocate_device(&client->dev);
	if (IS_ERR(rtc))
		return PTR_ERR(rtc);

	rtc->ops = &isl1208_rtc_ops;

	i2c_set_clientdata(client, rtc);
	dev_set_drvdata(&rtc->dev, client);

	rc = isl1208_i2c_get_sr(client);
	if (rc < 0) {
		dev_err(&client->dev, "reading status failed\n");
		return rc;
	}

	if (rc & ISL1208_REG_SR_RTCF)
		dev_warn(&client->dev, "rtc power failure detected, "
			 "please set clock.\n");

	if (id->driver_data == TYPE_ISL1219) {
		struct device_node *np = client->dev.of_node;
		u32 evienb;

		rc = i2c_smbus_read_byte_data(client, ISL1219_REG_EV);
		if (rc < 0) {
			dev_err(&client->dev, "failed to read EV reg\n");
			return rc;
		}
		rc |= ISL1219_REG_EV_EVEN;
		if (!of_property_read_u32(np, "isil,ev-evienb", &evienb)) {
			if (evienb)
				rc |= ISL1219_REG_EV_EVIENB;
			else
				rc &= ~ISL1219_REG_EV_EVIENB;
		}
		rc = i2c_smbus_write_byte_data(client, ISL1219_REG_EV, rc);
		if (rc < 0) {
			dev_err(&client->dev, "could not enable tamper detection\n");
			return rc;
		}
		rc = rtc_add_group(rtc, &isl1219_rtc_sysfs_files);
		if (rc)
			return rc;
		evdet_irq = of_irq_get_byname(np, "evdet");
	}

	rc = sysfs_create_group(&client->dev.kobj, &isl1208_rtc_sysfs_files);
	if (rc)
		return rc;

	if (client->irq > 0)
		rc = isl1208_setup_irq(client, client->irq);
	if (rc)
		return rc;

	if (evdet_irq > 0 && evdet_irq != client->irq)
		rc = isl1208_setup_irq(client, evdet_irq);
	if (rc)
		return rc;

	return rtc_register_device(rtc);
}