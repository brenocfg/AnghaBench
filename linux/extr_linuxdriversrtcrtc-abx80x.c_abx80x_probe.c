#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct rtc_device {int /*<<< orphan*/ * ops; } ;
struct i2c_device_id {unsigned int driver_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; struct device_node* of_node; } ;
struct i2c_client {int irq; TYPE_1__ dev; int /*<<< orphan*/  adapter; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_9__ {int pn; scalar_t__ has_tc; } ;

/* Variables and functions */
 unsigned int ABX80X ; 
 int ABX8XX_CTRL_12_24 ; 
 int ABX8XX_CTRL_ARST ; 
 int ABX8XX_CTRL_WRITE ; 
 int /*<<< orphan*/  ABX8XX_REG_CD_TIMER_CTL ; 
 int /*<<< orphan*/  ABX8XX_REG_CTRL1 ; 
 int /*<<< orphan*/  ABX8XX_REG_ID0 ; 
 int BIT (int) ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 scalar_t__ IS_ERR (struct rtc_device*) ; 
 int PTR_ERR (struct rtc_device*) ; 
 TYPE_7__* abx80x_caps ; 
 int abx80x_dt_trickle_cfg (struct device_node*) ; 
 int /*<<< orphan*/  abx80x_enable_trickle_charger (struct i2c_client*,int) ; 
 int /*<<< orphan*/  abx80x_handle_irq ; 
 int /*<<< orphan*/  abx80x_rtc_ops ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int,...) ; 
 int devm_add_action_or_reset (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int devm_request_threaded_irq (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct i2c_client*) ; 
 struct rtc_device* devm_rtc_allocate_device (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rtc_device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,char*) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtc_calib_attr_group ; 
 int /*<<< orphan*/  rtc_calib_remove_sysfs_group ; 
 int rtc_register_device (struct rtc_device*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int abx80x_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct device_node *np = client->dev.of_node;
	struct rtc_device *rtc;
	int i, data, err, trickle_cfg = -EINVAL;
	char buf[7];
	unsigned int part = id->driver_data;
	unsigned int partnumber;
	unsigned int majrev, minrev;
	unsigned int lot;
	unsigned int wafer;
	unsigned int uid;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		return -ENODEV;

	err = i2c_smbus_read_i2c_block_data(client, ABX8XX_REG_ID0,
					    sizeof(buf), buf);
	if (err < 0) {
		dev_err(&client->dev, "Unable to read partnumber\n");
		return -EIO;
	}

	partnumber = (buf[0] << 8) | buf[1];
	majrev = buf[2] >> 3;
	minrev = buf[2] & 0x7;
	lot = ((buf[4] & 0x80) << 2) | ((buf[6] & 0x80) << 1) | buf[3];
	uid = ((buf[4] & 0x7f) << 8) | buf[5];
	wafer = (buf[6] & 0x7c) >> 2;
	dev_info(&client->dev, "model %04x, revision %u.%u, lot %x, wafer %x, uid %x\n",
		 partnumber, majrev, minrev, lot, wafer, uid);

	data = i2c_smbus_read_byte_data(client, ABX8XX_REG_CTRL1);
	if (data < 0) {
		dev_err(&client->dev, "Unable to read control register\n");
		return -EIO;
	}

	err = i2c_smbus_write_byte_data(client, ABX8XX_REG_CTRL1,
					((data & ~(ABX8XX_CTRL_12_24 |
						   ABX8XX_CTRL_ARST)) |
					 ABX8XX_CTRL_WRITE));
	if (err < 0) {
		dev_err(&client->dev, "Unable to write control register\n");
		return -EIO;
	}

	/* part autodetection */
	if (part == ABX80X) {
		for (i = 0; abx80x_caps[i].pn; i++)
			if (partnumber == abx80x_caps[i].pn)
				break;
		if (abx80x_caps[i].pn == 0) {
			dev_err(&client->dev, "Unknown part: %04x\n",
				partnumber);
			return -EINVAL;
		}
		part = i;
	}

	if (partnumber != abx80x_caps[part].pn) {
		dev_err(&client->dev, "partnumber mismatch %04x != %04x\n",
			partnumber, abx80x_caps[part].pn);
		return -EINVAL;
	}

	if (np && abx80x_caps[part].has_tc)
		trickle_cfg = abx80x_dt_trickle_cfg(np);

	if (trickle_cfg > 0) {
		dev_info(&client->dev, "Enabling trickle charger: %02x\n",
			 trickle_cfg);
		abx80x_enable_trickle_charger(client, trickle_cfg);
	}

	err = i2c_smbus_write_byte_data(client, ABX8XX_REG_CD_TIMER_CTL,
					BIT(2));
	if (err)
		return err;

	rtc = devm_rtc_allocate_device(&client->dev);
	if (IS_ERR(rtc))
		return PTR_ERR(rtc);

	rtc->ops = &abx80x_rtc_ops;

	i2c_set_clientdata(client, rtc);

	if (client->irq > 0) {
		dev_info(&client->dev, "IRQ %d supplied\n", client->irq);
		err = devm_request_threaded_irq(&client->dev, client->irq, NULL,
						abx80x_handle_irq,
						IRQF_SHARED | IRQF_ONESHOT,
						"abx8xx",
						client);
		if (err) {
			dev_err(&client->dev, "unable to request IRQ, alarms disabled\n");
			client->irq = 0;
		}
	}

	/* Export sysfs entries */
	err = sysfs_create_group(&(&client->dev)->kobj, &rtc_calib_attr_group);
	if (err) {
		dev_err(&client->dev, "Failed to create sysfs group: %d\n",
			err);
		return err;
	}

	err = devm_add_action_or_reset(&client->dev,
				       rtc_calib_remove_sysfs_group,
				       &client->dev);
	if (err) {
		dev_err(&client->dev,
			"Failed to add sysfs cleanup action: %d\n",
			err);
		return err;
	}

	err = rtc_register_device(rtc);

	return err;
}