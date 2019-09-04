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
struct nxp_nci_i2c_phy {void* gpio_fw; void* gpio_en; struct i2c_client* i2c_dev; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 void* desc_to_gpio (struct gpio_desc*) ; 
 struct gpio_desc* devm_gpiod_get_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int nxp_nci_i2c_acpi_config(struct nxp_nci_i2c_phy *phy)
{
	struct i2c_client *client = phy->i2c_dev;
	struct gpio_desc *gpiod_en, *gpiod_fw;

	gpiod_en = devm_gpiod_get_index(&client->dev, NULL, 2, GPIOD_OUT_LOW);
	gpiod_fw = devm_gpiod_get_index(&client->dev, NULL, 1, GPIOD_OUT_LOW);

	if (IS_ERR(gpiod_en) || IS_ERR(gpiod_fw)) {
		nfc_err(&client->dev, "No GPIOs\n");
		return -EINVAL;
	}

	phy->gpio_en = desc_to_gpio(gpiod_en);
	phy->gpio_fw = desc_to_gpio(gpiod_fw);

	return 0;
}