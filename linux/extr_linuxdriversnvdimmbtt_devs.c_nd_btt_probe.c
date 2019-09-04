#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nd_region {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct nd_namespace_common {int claim_class; TYPE_1__ dev; scalar_t__ force_raw; } ;
struct nd_btt {int /*<<< orphan*/  ndns; } ;
struct device {int dummy; } ;
struct btt_sb {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  NVDIMM_CCLASS_BTT 130 
#define  NVDIMM_CCLASS_BTT2 129 
#define  NVDIMM_CCLASS_NONE 128 
 struct device* __nd_btt_create (struct nd_region*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nd_namespace_common*) ; 
 int __nd_btt_probe (struct nd_btt*,struct nd_namespace_common*,struct btt_sb*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*) ; 
 char* dev_name (struct device*) ; 
 struct btt_sb* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd_detach_ndns (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct nd_btt* to_nd_btt (struct device*) ; 
 struct nd_region* to_nd_region (int /*<<< orphan*/ ) ; 

int nd_btt_probe(struct device *dev, struct nd_namespace_common *ndns)
{
	int rc;
	struct device *btt_dev;
	struct btt_sb *btt_sb;
	struct nd_region *nd_region = to_nd_region(ndns->dev.parent);

	if (ndns->force_raw)
		return -ENODEV;

	switch (ndns->claim_class) {
	case NVDIMM_CCLASS_NONE:
	case NVDIMM_CCLASS_BTT:
	case NVDIMM_CCLASS_BTT2:
		break;
	default:
		return -ENODEV;
	}

	nvdimm_bus_lock(&ndns->dev);
	btt_dev = __nd_btt_create(nd_region, 0, NULL, ndns);
	nvdimm_bus_unlock(&ndns->dev);
	if (!btt_dev)
		return -ENOMEM;
	btt_sb = devm_kzalloc(dev, sizeof(*btt_sb), GFP_KERNEL);
	rc = __nd_btt_probe(to_nd_btt(btt_dev), ndns, btt_sb);
	dev_dbg(dev, "btt: %s\n", rc == 0 ? dev_name(btt_dev) : "<none>");
	if (rc < 0) {
		struct nd_btt *nd_btt = to_nd_btt(btt_dev);

		nd_detach_ndns(btt_dev, &nd_btt->ndns);
		put_device(btt_dev);
	}

	return rc;
}