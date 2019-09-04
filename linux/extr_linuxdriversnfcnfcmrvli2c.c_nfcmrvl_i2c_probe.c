#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct nfcmrvl_platform_data {int irq_polarity; int /*<<< orphan*/  irq; } ;
struct nfcmrvl_i2c_drv_data {TYPE_1__* priv; struct i2c_client* i2c; TYPE_2__* dev; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_9__ {scalar_t__ of_node; struct nfcmrvl_platform_data* platform_data; } ;
struct i2c_client {TYPE_2__ dev; int /*<<< orphan*/  adapter; } ;
struct TYPE_8__ {int support_fw_dnld; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  NFCMRVL_PHY_I2C ; 
 int PTR_ERR (TYPE_1__*) ; 
 struct nfcmrvl_i2c_drv_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct nfcmrvl_i2c_drv_data*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_ops ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct nfcmrvl_i2c_drv_data*) ; 
 int /*<<< orphan*/  nfc_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  nfcmrvl_i2c_int_irq_thread_fn ; 
 scalar_t__ nfcmrvl_i2c_parse_dt (scalar_t__,struct nfcmrvl_platform_data*) ; 
 TYPE_1__* nfcmrvl_nci_register_dev (int /*<<< orphan*/ ,struct nfcmrvl_i2c_drv_data*,int /*<<< orphan*/ *,TYPE_2__*,struct nfcmrvl_platform_data*) ; 

__attribute__((used)) static int nfcmrvl_i2c_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	struct nfcmrvl_i2c_drv_data *drv_data;
	struct nfcmrvl_platform_data *pdata;
	struct nfcmrvl_platform_data config;
	int ret;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		nfc_err(&client->dev, "Need I2C_FUNC_I2C\n");
		return -ENODEV;
	}

	drv_data = devm_kzalloc(&client->dev, sizeof(*drv_data), GFP_KERNEL);
	if (!drv_data)
		return -ENOMEM;

	drv_data->i2c = client;
	drv_data->dev = &client->dev;
	drv_data->priv = NULL;

	i2c_set_clientdata(client, drv_data);

	pdata = client->dev.platform_data;

	if (!pdata && client->dev.of_node)
		if (nfcmrvl_i2c_parse_dt(client->dev.of_node, &config) == 0)
			pdata = &config;

	if (!pdata)
		return -EINVAL;

	/* Request the read IRQ */
	ret = devm_request_threaded_irq(&drv_data->i2c->dev, pdata->irq,
					NULL, nfcmrvl_i2c_int_irq_thread_fn,
					pdata->irq_polarity | IRQF_ONESHOT,
					"nfcmrvl_i2c_int", drv_data);
	if (ret < 0) {
		nfc_err(&drv_data->i2c->dev,
			"Unable to register IRQ handler\n");
		return ret;
	}

	drv_data->priv = nfcmrvl_nci_register_dev(NFCMRVL_PHY_I2C,
						  drv_data, &i2c_ops,
						  &drv_data->i2c->dev, pdata);

	if (IS_ERR(drv_data->priv))
		return PTR_ERR(drv_data->priv);

	drv_data->priv->support_fw_dnld = true;

	return 0;
}