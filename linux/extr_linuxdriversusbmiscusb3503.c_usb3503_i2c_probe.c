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
struct usb3503 {int /*<<< orphan*/ * dev; int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct usb3503* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct usb3503*) ; 
 int usb3503_probe (struct usb3503*) ; 
 int /*<<< orphan*/  usb3503_regmap_config ; 

__attribute__((used)) static int usb3503_i2c_probe(struct i2c_client *i2c,
			     const struct i2c_device_id *id)
{
	struct usb3503 *hub;
	int err;

	hub = devm_kzalloc(&i2c->dev, sizeof(struct usb3503), GFP_KERNEL);
	if (!hub)
		return -ENOMEM;

	i2c_set_clientdata(i2c, hub);
	hub->regmap = devm_regmap_init_i2c(i2c, &usb3503_regmap_config);
	if (IS_ERR(hub->regmap)) {
		err = PTR_ERR(hub->regmap);
		dev_err(&i2c->dev, "Failed to initialise regmap: %d\n", err);
		return err;
	}
	hub->dev = &i2c->dev;

	return usb3503_probe(hub);
}