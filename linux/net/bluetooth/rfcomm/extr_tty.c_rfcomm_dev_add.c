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
struct rfcomm_dlc {int dummy; } ;
struct rfcomm_dev_req {int /*<<< orphan*/  channel; int /*<<< orphan*/  dev_id; } ;
struct rfcomm_dev {int id; struct rfcomm_dev* tty_dev; int /*<<< orphan*/  port; } ;
struct device {int id; struct device* tty_dev; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 scalar_t__ IS_ERR (struct rfcomm_dev*) ; 
 int PTR_ERR (struct rfcomm_dev*) ; 
 struct rfcomm_dev* __rfcomm_dev_add (struct rfcomm_dev_req*,struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  dev_attr_address ; 
 int /*<<< orphan*/  dev_attr_channel ; 
 int /*<<< orphan*/  dev_set_drvdata (struct rfcomm_dev*,struct rfcomm_dev*) ; 
 scalar_t__ device_create_file (struct rfcomm_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfcomm_dlc_put (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_reparent_device (struct rfcomm_dev*) ; 
 int /*<<< orphan*/  rfcomm_tty_driver ; 
 int /*<<< orphan*/  tty_port_put (int /*<<< orphan*/ *) ; 
 struct rfcomm_dev* tty_port_register_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rfcomm_dev_add(struct rfcomm_dev_req *req, struct rfcomm_dlc *dlc)
{
	struct rfcomm_dev *dev;
	struct device *tty;

	BT_DBG("id %d channel %d", req->dev_id, req->channel);

	dev = __rfcomm_dev_add(req, dlc);
	if (IS_ERR(dev)) {
		rfcomm_dlc_put(dlc);
		return PTR_ERR(dev);
	}

	tty = tty_port_register_device(&dev->port, rfcomm_tty_driver,
			dev->id, NULL);
	if (IS_ERR(tty)) {
		tty_port_put(&dev->port);
		return PTR_ERR(tty);
	}

	dev->tty_dev = tty;
	rfcomm_reparent_device(dev);
	dev_set_drvdata(dev->tty_dev, dev);

	if (device_create_file(dev->tty_dev, &dev_attr_address) < 0)
		BT_ERR("Failed to create address attribute");

	if (device_create_file(dev->tty_dev, &dev_attr_channel) < 0)
		BT_ERR("Failed to create channel attribute");

	return dev->id;
}