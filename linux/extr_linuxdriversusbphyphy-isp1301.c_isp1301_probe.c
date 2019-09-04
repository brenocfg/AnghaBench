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
struct usb_phy {int /*<<< orphan*/  type; int /*<<< orphan*/  set_vbus; int /*<<< orphan*/  init; int /*<<< orphan*/  label; int /*<<< orphan*/ * dev; } ;
struct isp1301 {struct usb_phy phy; int /*<<< orphan*/  mutex; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_PHY_TYPE_USB2 ; 
 struct isp1301* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct isp1301*) ; 
 struct i2c_client* isp1301_i2c_client ; 
 int /*<<< orphan*/  isp1301_phy_init ; 
 int /*<<< orphan*/  isp1301_phy_set_vbus ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_add_phy_dev (struct usb_phy*) ; 

__attribute__((used)) static int isp1301_probe(struct i2c_client *client,
			 const struct i2c_device_id *i2c_id)
{
	struct isp1301 *isp;
	struct usb_phy *phy;

	isp = devm_kzalloc(&client->dev, sizeof(*isp), GFP_KERNEL);
	if (!isp)
		return -ENOMEM;

	isp->client = client;
	mutex_init(&isp->mutex);

	phy = &isp->phy;
	phy->dev = &client->dev;
	phy->label = DRV_NAME;
	phy->init = isp1301_phy_init;
	phy->set_vbus = isp1301_phy_set_vbus;
	phy->type = USB_PHY_TYPE_USB2;

	i2c_set_clientdata(client, isp);
	usb_add_phy_dev(phy);

	isp1301_i2c_client = client;

	return 0;
}