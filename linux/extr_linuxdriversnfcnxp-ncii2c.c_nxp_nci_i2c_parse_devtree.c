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
struct nxp_nci_i2c_phy {int gpio_en; int gpio_fw; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPROBE_DEFER ; 
 struct nxp_nci_i2c_phy* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  nfc_err (TYPE_1__*,char*,int) ; 
 int of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nxp_nci_i2c_parse_devtree(struct i2c_client *client)
{
	struct nxp_nci_i2c_phy *phy = i2c_get_clientdata(client);
	struct device_node *pp;
	int r;

	pp = client->dev.of_node;
	if (!pp)
		return -ENODEV;

	r = of_get_named_gpio(pp, "enable-gpios", 0);
	if (r == -EPROBE_DEFER)
		r = of_get_named_gpio(pp, "enable-gpios", 0);
	if (r < 0) {
		nfc_err(&client->dev, "Failed to get EN gpio, error: %d\n", r);
		return r;
	}
	phy->gpio_en = r;

	r = of_get_named_gpio(pp, "firmware-gpios", 0);
	if (r == -EPROBE_DEFER)
		r = of_get_named_gpio(pp, "firmware-gpios", 0);
	if (r < 0) {
		nfc_err(&client->dev, "Failed to get FW gpio, error: %d\n", r);
		return r;
	}
	phy->gpio_fw = r;

	return 0;
}