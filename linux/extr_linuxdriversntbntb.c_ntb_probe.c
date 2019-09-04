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
struct ntb_dev {int dummy; } ;
struct TYPE_2__ {int (* probe ) (struct ntb_client*,struct ntb_dev*) ;} ;
struct ntb_client {TYPE_1__ ops; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 struct ntb_dev* dev_ntb (struct device*) ; 
 struct ntb_client* drv_ntb_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int stub1 (struct ntb_client*,struct ntb_dev*) ; 

__attribute__((used)) static int ntb_probe(struct device *dev)
{
	struct ntb_dev *ntb;
	struct ntb_client *client;
	int rc;

	get_device(dev);
	ntb = dev_ntb(dev);
	client = drv_ntb_client(dev->driver);

	rc = client->ops.probe(client, ntb);
	if (rc)
		put_device(dev);

	return rc;
}