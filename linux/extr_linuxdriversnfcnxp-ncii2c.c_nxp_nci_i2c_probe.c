#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nxp_nci_nfc_platform_data {int /*<<< orphan*/  gpio_fw; int /*<<< orphan*/  gpio_en; } ;
struct nxp_nci_i2c_phy {int /*<<< orphan*/  ndev; int /*<<< orphan*/  gpio_fw; struct i2c_client* i2c_dev; int /*<<< orphan*/  gpio_en; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_6__ {scalar_t__ of_node; struct nxp_nci_nfc_platform_data* platform_data; } ;
struct i2c_client {TYPE_1__ dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 scalar_t__ ACPI_HANDLE (TYPE_1__*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  NXP_NCI_I2C_DRIVER_NAME ; 
 int /*<<< orphan*/  NXP_NCI_I2C_MAX_PAYLOAD ; 
 int devm_gpio_request_one (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct nxp_nci_i2c_phy* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_phy_ops ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct nxp_nci_i2c_phy*) ; 
 int /*<<< orphan*/  nfc_err (TYPE_1__*,char*) ; 
 int nxp_nci_i2c_acpi_config (struct nxp_nci_i2c_phy*) ; 
 int /*<<< orphan*/  nxp_nci_i2c_irq_thread_fn ; 
 int nxp_nci_i2c_parse_devtree (struct i2c_client*) ; 
 int nxp_nci_probe (struct nxp_nci_i2c_phy*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct nxp_nci_i2c_phy*) ; 

__attribute__((used)) static int nxp_nci_i2c_probe(struct i2c_client *client,
			    const struct i2c_device_id *id)
{
	struct nxp_nci_i2c_phy *phy;
	struct nxp_nci_nfc_platform_data *pdata;
	int r;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		nfc_err(&client->dev, "Need I2C_FUNC_I2C\n");
		r = -ENODEV;
		goto probe_exit;
	}

	phy = devm_kzalloc(&client->dev, sizeof(struct nxp_nci_i2c_phy),
			   GFP_KERNEL);
	if (!phy) {
		r = -ENOMEM;
		goto probe_exit;
	}

	phy->i2c_dev = client;
	i2c_set_clientdata(client, phy);

	pdata = client->dev.platform_data;

	if (!pdata && client->dev.of_node) {
		r = nxp_nci_i2c_parse_devtree(client);
		if (r < 0) {
			nfc_err(&client->dev, "Failed to get DT data\n");
			goto probe_exit;
		}
	} else if (pdata) {
		phy->gpio_en = pdata->gpio_en;
		phy->gpio_fw = pdata->gpio_fw;
	} else if (ACPI_HANDLE(&client->dev)) {
		r = nxp_nci_i2c_acpi_config(phy);
		if (r < 0)
			goto probe_exit;
		goto nci_probe;
	} else {
		nfc_err(&client->dev, "No platform data\n");
		r = -EINVAL;
		goto probe_exit;
	}

	r = devm_gpio_request_one(&phy->i2c_dev->dev, phy->gpio_en,
				  GPIOF_OUT_INIT_LOW, "nxp_nci_en");
	if (r < 0)
		goto probe_exit;

	r = devm_gpio_request_one(&phy->i2c_dev->dev, phy->gpio_fw,
				  GPIOF_OUT_INIT_LOW, "nxp_nci_fw");
	if (r < 0)
		goto probe_exit;

nci_probe:
	r = nxp_nci_probe(phy, &client->dev, &i2c_phy_ops,
			  NXP_NCI_I2C_MAX_PAYLOAD, &phy->ndev);
	if (r < 0)
		goto probe_exit;

	r = request_threaded_irq(client->irq, NULL,
				 nxp_nci_i2c_irq_thread_fn,
				 IRQF_TRIGGER_RISING | IRQF_ONESHOT,
				 NXP_NCI_I2C_DRIVER_NAME, phy);
	if (r < 0)
		nfc_err(&client->dev, "Unable to register IRQ handler\n");

probe_exit:
	return r;
}