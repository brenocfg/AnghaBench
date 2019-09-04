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
struct TYPE_2__ {int /*<<< orphan*/  (* remove ) (struct ntb_client*,struct ntb_dev*) ;} ;
struct ntb_client {TYPE_1__ ops; } ;
struct device {scalar_t__ driver; } ;

/* Variables and functions */
 struct ntb_dev* dev_ntb (struct device*) ; 
 struct ntb_client* drv_ntb_client (scalar_t__) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct ntb_client*,struct ntb_dev*) ; 

__attribute__((used)) static int ntb_remove(struct device *dev)
{
	struct ntb_dev *ntb;
	struct ntb_client *client;

	if (dev->driver) {
		ntb = dev_ntb(dev);
		client = drv_ntb_client(dev->driver);

		client->ops.remove(client, ntb);
		put_device(dev);
	}

	return 0;
}