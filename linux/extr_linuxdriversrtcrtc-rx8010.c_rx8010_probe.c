#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct rx8010_data {TYPE_2__* rtc; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  parent; } ;
struct i2c_client {scalar_t__ irq; TYPE_3__ dev; int /*<<< orphan*/  name; } ;
struct i2c_adapter {TYPE_3__ dev; } ;
struct TYPE_12__ {int max_user_freq; } ;
struct TYPE_11__ {int /*<<< orphan*/  alarm_irq_enable; int /*<<< orphan*/  set_alarm; int /*<<< orphan*/  read_alarm; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_I2C_BLOCK ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*,scalar_t__) ; 
 struct rx8010_data* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_3__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct i2c_client*) ; 
 TYPE_2__* devm_rtc_device_register (TYPE_3__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rx8010_data*) ; 
 int /*<<< orphan*/  rx8010_alarm_irq_enable ; 
 int rx8010_init_client (struct i2c_client*) ; 
 int /*<<< orphan*/  rx8010_irq_1_handler ; 
 int /*<<< orphan*/  rx8010_read_alarm ; 
 TYPE_1__ rx8010_rtc_ops ; 
 int /*<<< orphan*/  rx8010_set_alarm ; 
 struct i2c_adapter* to_i2c_adapter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rx8010_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);
	struct rx8010_data *rx8010;
	int err = 0;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA
		| I2C_FUNC_SMBUS_I2C_BLOCK)) {
		dev_err(&adapter->dev, "doesn't support required functionality\n");
		return -EIO;
	}

	rx8010 = devm_kzalloc(&client->dev, sizeof(struct rx8010_data),
			      GFP_KERNEL);
	if (!rx8010)
		return -ENOMEM;

	rx8010->client = client;
	i2c_set_clientdata(client, rx8010);

	err = rx8010_init_client(client);
	if (err)
		return err;

	if (client->irq > 0) {
		dev_info(&client->dev, "IRQ %d supplied\n", client->irq);
		err = devm_request_threaded_irq(&client->dev, client->irq, NULL,
						rx8010_irq_1_handler,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						"rx8010", client);

		if (err) {
			dev_err(&client->dev, "unable to request IRQ\n");
			client->irq = 0;
		} else {
			rx8010_rtc_ops.read_alarm = rx8010_read_alarm;
			rx8010_rtc_ops.set_alarm = rx8010_set_alarm;
			rx8010_rtc_ops.alarm_irq_enable = rx8010_alarm_irq_enable;
		}
	}

	rx8010->rtc = devm_rtc_device_register(&client->dev, client->name,
		&rx8010_rtc_ops, THIS_MODULE);

	if (IS_ERR(rx8010->rtc)) {
		dev_err(&client->dev, "unable to register the class device\n");
		return PTR_ERR(rx8010->rtc);
	}

	rx8010->rtc->max_user_freq = 1;

	return err;
}