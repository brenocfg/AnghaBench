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
struct resource {scalar_t__ start; scalar_t__ end; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
struct nd_region {scalar_t__ ndr_size; scalar_t__ ndr_start; int /*<<< orphan*/  dev; } ;
struct device {int /*<<< orphan*/ * parent; int /*<<< orphan*/ * type; } ;
struct TYPE_2__ {struct device dev; } ;
struct nd_namespace_io {struct resource res; TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct device** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nd_namespace_io*) ; 
 struct nd_namespace_io* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namespace_io_device_type ; 

__attribute__((used)) static struct device **create_namespace_io(struct nd_region *nd_region)
{
	struct nd_namespace_io *nsio;
	struct device *dev, **devs;
	struct resource *res;

	nsio = kzalloc(sizeof(*nsio), GFP_KERNEL);
	if (!nsio)
		return NULL;

	devs = kcalloc(2, sizeof(struct device *), GFP_KERNEL);
	if (!devs) {
		kfree(nsio);
		return NULL;
	}

	dev = &nsio->common.dev;
	dev->type = &namespace_io_device_type;
	dev->parent = &nd_region->dev;
	res = &nsio->res;
	res->name = dev_name(&nd_region->dev);
	res->flags = IORESOURCE_MEM;
	res->start = nd_region->ndr_start;
	res->end = res->start + nd_region->ndr_size - 1;

	devs[0] = dev;
	return devs;
}