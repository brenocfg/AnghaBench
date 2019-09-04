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
struct mii_bus {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  _devm_mdiobus_free ; 
 int /*<<< orphan*/  devres_add (struct device*,struct mii_bus**) ; 
 struct mii_bus** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct mii_bus**) ; 
 struct mii_bus* mdiobus_alloc_size (int) ; 

struct mii_bus *devm_mdiobus_alloc_size(struct device *dev, int sizeof_priv)
{
	struct mii_bus **ptr, *bus;

	ptr = devres_alloc(_devm_mdiobus_free, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return NULL;

	/* use raw alloc_dr for kmalloc caller tracing */
	bus = mdiobus_alloc_size(sizeof_priv);
	if (bus) {
		*ptr = bus;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return bus;
}