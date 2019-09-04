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
struct nvdimm_bus_descriptor {char const* provider_name; } ;
struct TYPE_2__ {struct device* parent; } ;
struct nvdimm_bus {TYPE_1__ dev; struct nvdimm_bus_descriptor* nd_desc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 char const* dev_name (struct device*) ; 

__attribute__((used)) static const char *nvdimm_bus_provider(struct nvdimm_bus *nvdimm_bus)
{
	struct nvdimm_bus_descriptor *nd_desc = nvdimm_bus->nd_desc;
	struct device *parent = nvdimm_bus->dev.parent;

	if (nd_desc->provider_name)
		return nd_desc->provider_name;
	else if (parent)
		return dev_name(parent);
	else
		return "unknown";
}