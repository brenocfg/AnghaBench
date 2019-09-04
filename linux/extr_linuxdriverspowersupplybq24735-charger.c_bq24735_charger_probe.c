#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_9__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct power_supply_desc {char* name; int /*<<< orphan*/  property_is_writeable; int /*<<< orphan*/  set_property; int /*<<< orphan*/  get_property; int /*<<< orphan*/  num_properties; int /*<<< orphan*/  properties; int /*<<< orphan*/  type; } ;
struct power_supply_config {struct bq24735* drv_data; scalar_t__ of_node; int /*<<< orphan*/  num_supplicants; int /*<<< orphan*/  supplied_to; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_10__ {scalar_t__ of_node; TYPE_9__* platform_data; } ;
struct i2c_client {int irq; TYPE_1__ dev; } ;
struct bq24735 {int charging; int /*<<< orphan*/  poll_interval; int /*<<< orphan*/  poll; int /*<<< orphan*/  charger; int /*<<< orphan*/  status_gpio; TYPE_9__* pdata; struct power_supply_desc charger_desc; struct i2c_client* client; int /*<<< orphan*/  lock; } ;
struct TYPE_11__ {int /*<<< orphan*/  num_supplicants; int /*<<< orphan*/  supplied_to; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BQ24735_DEVICE_ID ; 
 int /*<<< orphan*/  BQ24735_MANUFACTURER_ID ; 
 int /*<<< orphan*/  CONFIG_OF ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POWER_SUPPLY_TYPE_MAINS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bq24735_charger_get_property ; 
 scalar_t__ bq24735_charger_is_present (struct bq24735*) ; 
 int /*<<< orphan*/  bq24735_charger_isr ; 
 int /*<<< orphan*/  bq24735_charger_properties ; 
 int /*<<< orphan*/  bq24735_charger_property_is_writeable ; 
 int /*<<< orphan*/  bq24735_charger_set_property ; 
 int bq24735_enable_charging (struct bq24735*) ; 
 TYPE_9__* bq24735_parse_dt_data (struct i2c_client*) ; 
 int /*<<< orphan*/  bq24735_poll ; 
 int bq24735_read_word (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int device_property_read_u32 (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 char* devm_kasprintf (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct bq24735* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_power_supply_register (TYPE_1__*,struct power_supply_desc*,struct power_supply_config*) ; 
 int devm_request_threaded_irq (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct bq24735*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bq24735_charger_probe(struct i2c_client *client,
				 const struct i2c_device_id *id)
{
	int ret;
	struct bq24735 *charger;
	struct power_supply_desc *supply_desc;
	struct power_supply_config psy_cfg = {};
	char *name;

	charger = devm_kzalloc(&client->dev, sizeof(*charger), GFP_KERNEL);
	if (!charger)
		return -ENOMEM;

	mutex_init(&charger->lock);
	charger->charging = true;
	charger->pdata = client->dev.platform_data;

	if (IS_ENABLED(CONFIG_OF) && !charger->pdata && client->dev.of_node)
		charger->pdata = bq24735_parse_dt_data(client);

	if (!charger->pdata) {
		dev_err(&client->dev, "no platform data provided\n");
		return -EINVAL;
	}

	name = (char *)charger->pdata->name;
	if (!name) {
		name = devm_kasprintf(&client->dev, GFP_KERNEL,
				      "bq24735@%s",
				      dev_name(&client->dev));
		if (!name) {
			dev_err(&client->dev, "Failed to alloc device name\n");
			return -ENOMEM;
		}
	}

	charger->client = client;

	supply_desc = &charger->charger_desc;

	supply_desc->name = name;
	supply_desc->type = POWER_SUPPLY_TYPE_MAINS;
	supply_desc->properties = bq24735_charger_properties;
	supply_desc->num_properties = ARRAY_SIZE(bq24735_charger_properties);
	supply_desc->get_property = bq24735_charger_get_property;
	supply_desc->set_property = bq24735_charger_set_property;
	supply_desc->property_is_writeable =
				bq24735_charger_property_is_writeable;

	psy_cfg.supplied_to = charger->pdata->supplied_to;
	psy_cfg.num_supplicants = charger->pdata->num_supplicants;
	psy_cfg.of_node = client->dev.of_node;
	psy_cfg.drv_data = charger;

	i2c_set_clientdata(client, charger);

	charger->status_gpio = devm_gpiod_get_optional(&client->dev,
						       "ti,ac-detect",
						       GPIOD_IN);
	if (IS_ERR(charger->status_gpio)) {
		ret = PTR_ERR(charger->status_gpio);
		dev_err(&client->dev, "Getting gpio failed: %d\n", ret);
		return ret;
	}

	if (bq24735_charger_is_present(charger)) {
		ret = bq24735_read_word(client, BQ24735_MANUFACTURER_ID);
		if (ret < 0) {
			dev_err(&client->dev, "Failed to read manufacturer id : %d\n",
				ret);
			return ret;
		} else if (ret != 0x0040) {
			dev_err(&client->dev,
				"manufacturer id mismatch. 0x0040 != 0x%04x\n", ret);
			return -ENODEV;
		}

		ret = bq24735_read_word(client, BQ24735_DEVICE_ID);
		if (ret < 0) {
			dev_err(&client->dev, "Failed to read device id : %d\n", ret);
			return ret;
		} else if (ret != 0x000B) {
			dev_err(&client->dev,
				"device id mismatch. 0x000b != 0x%04x\n", ret);
			return -ENODEV;
		}

		ret = bq24735_enable_charging(charger);
		if (ret < 0) {
			dev_err(&client->dev, "Failed to enable charging\n");
			return ret;
		}
	}

	charger->charger = devm_power_supply_register(&client->dev, supply_desc,
						      &psy_cfg);
	if (IS_ERR(charger->charger)) {
		ret = PTR_ERR(charger->charger);
		dev_err(&client->dev, "Failed to register power supply: %d\n",
			ret);
		return ret;
	}

	if (client->irq) {
		ret = devm_request_threaded_irq(&client->dev, client->irq,
						NULL, bq24735_charger_isr,
						IRQF_TRIGGER_RISING |
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
						supply_desc->name,
						charger->charger);
		if (ret) {
			dev_err(&client->dev,
				"Unable to register IRQ %d err %d\n",
				client->irq, ret);
			return ret;
		}
	} else {
		ret = device_property_read_u32(&client->dev, "poll-interval",
					       &charger->poll_interval);
		if (ret)
			return 0;
		if (!charger->poll_interval)
			return 0;

		INIT_DELAYED_WORK(&charger->poll, bq24735_poll);
		schedule_delayed_work(&charger->poll,
				      msecs_to_jiffies(charger->poll_interval));
	}

	return 0;
}