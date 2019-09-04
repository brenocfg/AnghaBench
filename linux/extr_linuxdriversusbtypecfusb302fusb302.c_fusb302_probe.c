#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct i2c_device_id {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct i2c_client {struct device dev; scalar_t__ irq; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_4__ {TYPE_3__* config; } ;
struct TYPE_5__ {int operating_snk_mw; int /*<<< orphan*/  snk_pdo; int /*<<< orphan*/  nr_snk_pdo; } ;
struct fusb302_chip {int /*<<< orphan*/  wq; int /*<<< orphan*/  tcpm_port; scalar_t__ gpio_int_n_irq; struct device* dev; TYPE_1__ tcpc_dev; int /*<<< orphan*/  vbus; int /*<<< orphan*/  bc_lvl_handler; int /*<<< orphan*/  extcon; int /*<<< orphan*/  snk_pdo; TYPE_3__ tcpc_config; int /*<<< orphan*/  lock; struct i2c_client* i2c_client; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_I2C_BLOCK ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 scalar_t__ device_property_read_string (struct device*,char*,char const**) ; 
 int /*<<< orphan*/  device_property_read_u32 (struct device*,char*,int*) ; 
 struct fusb302_chip* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_get (struct device*,char*) ; 
 int devm_request_threaded_irq (struct device*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct fusb302_chip*) ; 
 int /*<<< orphan*/  enable_irq_wake (scalar_t__) ; 
 int /*<<< orphan*/  extcon_get_extcon_dev (char const*) ; 
 int /*<<< orphan*/  fusb302_bc_lvl_handler_work ; 
 int /*<<< orphan*/  fusb302_composite_snk_pdo_array (struct fusb302_chip*) ; 
 int /*<<< orphan*/  fusb302_debugfs_exit (struct fusb302_chip*) ; 
 int /*<<< orphan*/  fusb302_debugfs_init (struct fusb302_chip*) ; 
 int /*<<< orphan*/  fusb302_irq_intn ; 
 TYPE_3__ fusb302_tcpc_config ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct fusb302_chip*) ; 
 int init_gpio (struct fusb302_chip*) ; 
 int /*<<< orphan*/  init_tcpc_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcpm_register_port (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  tcpm_unregister_port (int /*<<< orphan*/ ) ; 
 struct i2c_adapter* to_i2c_adapter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fusb302_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct fusb302_chip *chip;
	struct i2c_adapter *adapter;
	struct device *dev = &client->dev;
	const char *name;
	int ret = 0;
	u32 v;

	adapter = to_i2c_adapter(client->dev.parent);
	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_I2C_BLOCK)) {
		dev_err(&client->dev,
			"I2C/SMBus block functionality not supported!\n");
		return -ENODEV;
	}
	chip = devm_kzalloc(&client->dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	chip->i2c_client = client;
	i2c_set_clientdata(client, chip);
	chip->dev = &client->dev;
	chip->tcpc_config = fusb302_tcpc_config;
	chip->tcpc_dev.config = &chip->tcpc_config;
	mutex_init(&chip->lock);

	if (!device_property_read_u32(dev, "fcs,operating-sink-microwatt", &v))
		chip->tcpc_config.operating_snk_mw = v / 1000;

	/* Composite sink PDO */
	chip->tcpc_config.nr_snk_pdo = fusb302_composite_snk_pdo_array(chip);
	chip->tcpc_config.snk_pdo = chip->snk_pdo;

	/*
	 * Devicetree platforms should get extcon via phandle (not yet
	 * supported). On ACPI platforms, we get the name from a device prop.
	 * This device prop is for kernel internal use only and is expected
	 * to be set by the platform code which also registers the i2c client
	 * for the fusb302.
	 */
	if (device_property_read_string(dev, "fcs,extcon-name", &name) == 0) {
		chip->extcon = extcon_get_extcon_dev(name);
		if (!chip->extcon)
			return -EPROBE_DEFER;
	}

	fusb302_debugfs_init(chip);

	chip->wq = create_singlethread_workqueue(dev_name(chip->dev));
	if (!chip->wq) {
		ret = -ENOMEM;
		goto clear_client_data;
	}
	INIT_DELAYED_WORK(&chip->bc_lvl_handler, fusb302_bc_lvl_handler_work);
	init_tcpc_dev(&chip->tcpc_dev);

	chip->vbus = devm_regulator_get(chip->dev, "vbus");
	if (IS_ERR(chip->vbus)) {
		ret = PTR_ERR(chip->vbus);
		goto destroy_workqueue;
	}

	if (client->irq) {
		chip->gpio_int_n_irq = client->irq;
	} else {
		ret = init_gpio(chip);
		if (ret < 0)
			goto destroy_workqueue;
	}

	chip->tcpm_port = tcpm_register_port(&client->dev, &chip->tcpc_dev);
	if (IS_ERR(chip->tcpm_port)) {
		ret = PTR_ERR(chip->tcpm_port);
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "cannot register tcpm port, ret=%d", ret);
		goto destroy_workqueue;
	}

	ret = devm_request_threaded_irq(chip->dev, chip->gpio_int_n_irq,
					NULL, fusb302_irq_intn,
					IRQF_ONESHOT | IRQF_TRIGGER_LOW,
					"fsc_interrupt_int_n", chip);
	if (ret < 0) {
		dev_err(dev, "cannot request IRQ for GPIO Int_N, ret=%d", ret);
		goto tcpm_unregister_port;
	}
	enable_irq_wake(chip->gpio_int_n_irq);
	return ret;

tcpm_unregister_port:
	tcpm_unregister_port(chip->tcpm_port);
destroy_workqueue:
	destroy_workqueue(chip->wq);
clear_client_data:
	i2c_set_clientdata(client, NULL);
	fusb302_debugfs_exit(chip);

	return ret;
}