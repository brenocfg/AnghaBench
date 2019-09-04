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
struct net_device {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,char*) ; 
 int request_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct net_device*) ; 

__attribute__((used)) static inline int ravb_hook_irq(unsigned int irq, irq_handler_t handler,
				struct net_device *ndev, struct device *dev,
				const char *ch)
{
	char *name;
	int error;

	name = devm_kasprintf(dev, GFP_KERNEL, "%s:%s", ndev->name, ch);
	if (!name)
		return -ENOMEM;
	error = request_irq(irq, handler, 0, name, ndev);
	if (error)
		netdev_err(ndev, "cannot request IRQ %s\n", name);

	return error;
}