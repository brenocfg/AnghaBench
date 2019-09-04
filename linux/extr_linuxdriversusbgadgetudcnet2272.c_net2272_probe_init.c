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
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  max_speed; int /*<<< orphan*/ * ops; } ;
struct net2272 {unsigned int irq; TYPE_1__ gadget; struct device* dev; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct net2272* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  driver_name ; 
 struct net2272* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net2272_ops ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct net2272 *net2272_probe_init(struct device *dev, unsigned int irq)
{
	struct net2272 *ret;

	if (!irq) {
		dev_dbg(dev, "No IRQ!\n");
		return ERR_PTR(-ENODEV);
	}

	/* alloc, and start init */
	ret = kzalloc(sizeof(*ret), GFP_KERNEL);
	if (!ret)
		return ERR_PTR(-ENOMEM);

	spin_lock_init(&ret->lock);
	ret->irq = irq;
	ret->dev = dev;
	ret->gadget.ops = &net2272_ops;
	ret->gadget.max_speed = USB_SPEED_HIGH;

	/* the "gadget" abstracts/virtualizes the controller */
	ret->gadget.name = driver_name;

	return ret;
}