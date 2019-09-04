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
typedef  int /*<<< orphan*/  u8 ;
struct resource {int dummy; } ;
struct nvdimm_drvdata {int dummy; } ;
struct nd_region {int /*<<< orphan*/  dev; struct nd_mapping* mapping; } ;
struct nd_namespace_label {int /*<<< orphan*/  uuid; int /*<<< orphan*/  dpa; } ;
struct nd_mapping {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NSLABEL_UUID_LEN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_namespace_blk (struct device*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * namespace_to_uuid (struct device*) ; 
 int /*<<< orphan*/  nd_dbg_dpa (struct nd_region*,struct nvdimm_drvdata*,struct resource*,char*,int) ; 
 struct resource* nsblk_add_resource (struct nd_region*,struct nvdimm_drvdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_nd_namespace_blk (struct device*) ; 
 struct nvdimm_drvdata* to_ndd (struct nd_mapping*) ; 

__attribute__((used)) static int add_namespace_resource(struct nd_region *nd_region,
		struct nd_namespace_label *nd_label, struct device **devs,
		int count)
{
	struct nd_mapping *nd_mapping = &nd_region->mapping[0];
	struct nvdimm_drvdata *ndd = to_ndd(nd_mapping);
	int i;

	for (i = 0; i < count; i++) {
		u8 *uuid = namespace_to_uuid(devs[i]);
		struct resource *res;

		if (IS_ERR_OR_NULL(uuid)) {
			WARN_ON(1);
			continue;
		}

		if (memcmp(uuid, nd_label->uuid, NSLABEL_UUID_LEN) != 0)
			continue;
		if (is_namespace_blk(devs[i])) {
			res = nsblk_add_resource(nd_region, ndd,
					to_nd_namespace_blk(devs[i]),
					__le64_to_cpu(nd_label->dpa));
			if (!res)
				return -ENXIO;
			nd_dbg_dpa(nd_region, ndd, res, "%d assign\n", count);
		} else {
			dev_err(&nd_region->dev,
					"error: conflicting extents for uuid: %pUb\n",
					nd_label->uuid);
			return -ENXIO;
		}
		break;
	}

	return i;
}