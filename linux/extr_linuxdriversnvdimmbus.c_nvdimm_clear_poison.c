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
typedef  unsigned int u32 ;
struct nvdimm_bus_descriptor {int (* ndctl ) (struct nvdimm_bus_descriptor*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nd_cmd_clear_error*,int,int*) ;} ;
struct nvdimm_bus {struct nvdimm_bus_descriptor* nd_desc; } ;
struct nd_cmd_clear_error {unsigned int address; unsigned int length; unsigned int clear_err_unit; long cleared; } ;
struct nd_cmd_ars_cap {unsigned int address; unsigned int length; unsigned int clear_err_unit; long cleared; } ;
struct device {int dummy; } ;
typedef  unsigned int phys_addr_t ;
typedef  int /*<<< orphan*/  clear_err ;
typedef  int /*<<< orphan*/  ars_cap ;

/* Variables and functions */
 long ENXIO ; 
 int /*<<< orphan*/  ND_CMD_ARS_CAP ; 
 int /*<<< orphan*/  ND_CMD_CLEAR_ERROR ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned int) ; 
 int /*<<< orphan*/  memalloc_noio_restore (unsigned int) ; 
 unsigned int memalloc_noio_save () ; 
 int /*<<< orphan*/  memset (struct nd_cmd_clear_error*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvdimm_account_cleared_poison (struct nvdimm_bus*,unsigned int,long) ; 
 int stub1 (struct nvdimm_bus_descriptor*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nd_cmd_clear_error*,int,int*) ; 
 int stub2 (struct nvdimm_bus_descriptor*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nd_cmd_clear_error*,int,int*) ; 
 struct nvdimm_bus* walk_to_nvdimm_bus (struct device*) ; 

long nvdimm_clear_poison(struct device *dev, phys_addr_t phys,
		unsigned int len)
{
	struct nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);
	struct nvdimm_bus_descriptor *nd_desc;
	struct nd_cmd_clear_error clear_err;
	struct nd_cmd_ars_cap ars_cap;
	u32 clear_err_unit, mask;
	unsigned int noio_flag;
	int cmd_rc, rc;

	if (!nvdimm_bus)
		return -ENXIO;

	nd_desc = nvdimm_bus->nd_desc;
	/*
	 * if ndctl does not exist, it's PMEM_LEGACY and
	 * we want to just pretend everything is handled.
	 */
	if (!nd_desc->ndctl)
		return len;

	memset(&ars_cap, 0, sizeof(ars_cap));
	ars_cap.address = phys;
	ars_cap.length = len;
	noio_flag = memalloc_noio_save();
	rc = nd_desc->ndctl(nd_desc, NULL, ND_CMD_ARS_CAP, &ars_cap,
			sizeof(ars_cap), &cmd_rc);
	memalloc_noio_restore(noio_flag);
	if (rc < 0)
		return rc;
	if (cmd_rc < 0)
		return cmd_rc;
	clear_err_unit = ars_cap.clear_err_unit;
	if (!clear_err_unit || !is_power_of_2(clear_err_unit))
		return -ENXIO;

	mask = clear_err_unit - 1;
	if ((phys | len) & mask)
		return -ENXIO;
	memset(&clear_err, 0, sizeof(clear_err));
	clear_err.address = phys;
	clear_err.length = len;
	noio_flag = memalloc_noio_save();
	rc = nd_desc->ndctl(nd_desc, NULL, ND_CMD_CLEAR_ERROR, &clear_err,
			sizeof(clear_err), &cmd_rc);
	memalloc_noio_restore(noio_flag);
	if (rc < 0)
		return rc;
	if (cmd_rc < 0)
		return cmd_rc;

	nvdimm_account_cleared_poison(nvdimm_bus, phys, clear_err.cleared);

	return clear_err.cleared;
}