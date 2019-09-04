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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct tcpci_chip {int /*<<< orphan*/  tcpci; TYPE_1__ data; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCPC_ALERT_MASK ; 
 int /*<<< orphan*/  _tcpci_irq ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct tcpci_chip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct tcpci_chip*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tcpci_chip*) ; 
 int regmap_raw_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tcpci_register_port (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  tcpci_regmap_config ; 
 int /*<<< orphan*/  tcpci_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcpci_probe(struct i2c_client *client,
		       const struct i2c_device_id *i2c_id)
{
	struct tcpci_chip *chip;
	int err;
	u16 val = 0;

	chip = devm_kzalloc(&client->dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	chip->data.regmap = devm_regmap_init_i2c(client, &tcpci_regmap_config);
	if (IS_ERR(chip->data.regmap))
		return PTR_ERR(chip->data.regmap);

	i2c_set_clientdata(client, chip);

	/* Disable chip interrupts before requesting irq */
	err = regmap_raw_write(chip->data.regmap, TCPC_ALERT_MASK, &val,
			       sizeof(u16));
	if (err < 0)
		return err;

	chip->tcpci = tcpci_register_port(&client->dev, &chip->data);
	if (IS_ERR(chip->tcpci))
		return PTR_ERR(chip->tcpci);

	err = devm_request_threaded_irq(&client->dev, client->irq, NULL,
					_tcpci_irq,
					IRQF_ONESHOT | IRQF_TRIGGER_LOW,
					dev_name(&client->dev), chip);
	if (err < 0) {
		tcpci_unregister_port(chip->tcpci);
		return err;
	}

	return 0;
}