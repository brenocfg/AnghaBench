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
struct net_device {int dummy; } ;
struct hdlc_proto {int /*<<< orphan*/  module; } ;
struct TYPE_2__ {struct hdlc_proto* proto; int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int detach_hdlc_protocol (struct net_device*) ; 
 TYPE_1__* dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/ * kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

int attach_hdlc_protocol(struct net_device *dev, struct hdlc_proto *proto,
			 size_t size)
{
	int err;

	err = detach_hdlc_protocol(dev);
	if (err)
		return err;

	if (!try_module_get(proto->module))
		return -ENOSYS;

	if (size) {
		dev_to_hdlc(dev)->state = kmalloc(size, GFP_KERNEL);
		if (dev_to_hdlc(dev)->state == NULL) {
			module_put(proto->module);
			return -ENOBUFS;
		}
	}
	dev_to_hdlc(dev)->proto = proto;

	return 0;
}