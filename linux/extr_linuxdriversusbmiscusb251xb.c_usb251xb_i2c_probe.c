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
struct usb251xb {struct i2c_client* i2c; int /*<<< orphan*/ * dev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct usb251xb* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct usb251xb*) ; 
 int usb251xb_probe (struct usb251xb*) ; 

__attribute__((used)) static int usb251xb_i2c_probe(struct i2c_client *i2c,
			      const struct i2c_device_id *id)
{
	struct usb251xb *hub;

	hub = devm_kzalloc(&i2c->dev, sizeof(struct usb251xb), GFP_KERNEL);
	if (!hub)
		return -ENOMEM;

	i2c_set_clientdata(i2c, hub);
	hub->dev = &i2c->dev;
	hub->i2c = i2c;

	return usb251xb_probe(hub);
}