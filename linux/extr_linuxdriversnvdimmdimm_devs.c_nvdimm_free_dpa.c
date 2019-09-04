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
struct resource {int /*<<< orphan*/  start; int /*<<< orphan*/  name; } ;
struct nvdimm_drvdata {int /*<<< orphan*/  dpa; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __release_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_nvdimm_bus_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

void nvdimm_free_dpa(struct nvdimm_drvdata *ndd, struct resource *res)
{
	WARN_ON_ONCE(!is_nvdimm_bus_locked(ndd->dev));
	kfree(res->name);
	__release_region(&ndd->dpa, res->start, resource_size(res));
}