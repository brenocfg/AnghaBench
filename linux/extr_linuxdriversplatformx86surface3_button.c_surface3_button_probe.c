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
struct surface3_button_data {struct platform_device** children; } ;
struct platform_device {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPANION (struct device*) ; 
 int BUTTON_TYPES ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct platform_device*) ; 
 int PTR_ERR (struct platform_device*) ; 
 int /*<<< orphan*/  SURFACE_BUTTON_OBJ_NAME ; 
 int /*<<< orphan*/  acpi_device_bid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct surface3_button_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int gpiod_count (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct surface3_button_data*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct platform_device* surface3_button_device_create (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  surface3_button_remove (struct i2c_client*) ; 
 int /*<<< orphan*/  surface3_button_surface3 ; 

__attribute__((used)) static int surface3_button_probe(struct i2c_client *client,
				 const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct surface3_button_data *priv;
	struct platform_device *pd;
	int i;
	int error;

	if (strncmp(acpi_device_bid(ACPI_COMPANION(&client->dev)),
		    SURFACE_BUTTON_OBJ_NAME,
		    strlen(SURFACE_BUTTON_OBJ_NAME)))
		return -ENODEV;

	error = gpiod_count(dev, NULL);
	if (error < 0) {
		dev_dbg(dev, "no GPIO attached, ignoring...\n");
		return error;
	}

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	i2c_set_clientdata(client, priv);

	for (i = 0; i < BUTTON_TYPES; i++) {
		pd = surface3_button_device_create(client,
						   surface3_button_surface3,
						   i == 0);
		if (IS_ERR(pd)) {
			error = PTR_ERR(pd);
			if (error != -ENODEV) {
				surface3_button_remove(client);
				return error;
			}
			continue;
		}

		priv->children[i] = pd;
	}

	if (!priv->children[0] && !priv->children[1])
		return -ENODEV;

	return 0;
}