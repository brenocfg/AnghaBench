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
struct nd_namespace_common {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  __nvdimm_namespace_capacity (struct nd_namespace_common*) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (int /*<<< orphan*/ *) ; 

resource_size_t nvdimm_namespace_capacity(struct nd_namespace_common *ndns)
{
	resource_size_t size;

	nvdimm_bus_lock(&ndns->dev);
	size = __nvdimm_namespace_capacity(ndns);
	nvdimm_bus_unlock(&ndns->dev);

	return size;
}