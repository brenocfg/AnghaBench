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
struct nd_namespace_common {int claim_class; int /*<<< orphan*/  dev; } ;
struct device {int /*<<< orphan*/ * parent; scalar_t__ driver; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EBUSY ; 
 size_t EINVAL ; 
 size_t ENODEV ; 
 size_t ENOMEM ; 
 size_t ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  NVDIMM_CCLASS_BTT 132 
#define  NVDIMM_CCLASS_BTT2 131 
#define  NVDIMM_CCLASS_DAX 130 
#define  NVDIMM_CCLASS_NONE 129 
#define  NVDIMM_CCLASS_PFN 128 
 scalar_t__ SZ_16M ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __nd_attach_ndns (struct device*,struct nd_namespace_common*,struct nd_namespace_common**) ; 
 scalar_t__ __nvdimm_namespace_capacity (struct nd_namespace_common*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 struct device* device_find_child (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_nd_btt (struct device*) ; 
 int /*<<< orphan*/  is_nd_dax (struct device*) ; 
 int /*<<< orphan*/  is_nd_pfn (struct device*) ; 
 int /*<<< orphan*/  is_nvdimm_bus_locked (struct device*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrndup (char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namespace_match ; 
 int /*<<< orphan*/  nd_detach_and_reset (struct device*,struct nd_namespace_common**) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strim (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 struct nd_namespace_common* to_ndns (struct device*) ; 

ssize_t nd_namespace_store(struct device *dev,
		struct nd_namespace_common **_ndns, const char *buf,
		size_t len)
{
	struct nd_namespace_common *ndns;
	struct device *found;
	char *name;

	if (dev->driver) {
		dev_dbg(dev, "namespace already active\n");
		return -EBUSY;
	}

	name = kstrndup(buf, len, GFP_KERNEL);
	if (!name)
		return -ENOMEM;
	strim(name);

	if (strncmp(name, "namespace", 9) == 0 || strcmp(name, "") == 0)
		/* pass */;
	else {
		len = -EINVAL;
		goto out;
	}

	ndns = *_ndns;
	if (strcmp(name, "") == 0) {
		nd_detach_and_reset(dev, _ndns);
		goto out;
	} else if (ndns) {
		dev_dbg(dev, "namespace already set to: %s\n",
				dev_name(&ndns->dev));
		len = -EBUSY;
		goto out;
	}

	found = device_find_child(dev->parent, name, namespace_match);
	if (!found) {
		dev_dbg(dev, "'%s' not found under %s\n", name,
				dev_name(dev->parent));
		len = -ENODEV;
		goto out;
	}

	ndns = to_ndns(found);

	switch (ndns->claim_class) {
	case NVDIMM_CCLASS_NONE:
		break;
	case NVDIMM_CCLASS_BTT:
	case NVDIMM_CCLASS_BTT2:
		if (!is_nd_btt(dev)) {
			len = -EBUSY;
			goto out_attach;
		}
		break;
	case NVDIMM_CCLASS_PFN:
		if (!is_nd_pfn(dev)) {
			len = -EBUSY;
			goto out_attach;
		}
		break;
	case NVDIMM_CCLASS_DAX:
		if (!is_nd_dax(dev)) {
			len = -EBUSY;
			goto out_attach;
		}
		break;
	default:
		len = -EBUSY;
		goto out_attach;
		break;
	}

	if (__nvdimm_namespace_capacity(ndns) < SZ_16M) {
		dev_dbg(dev, "%s too small to host\n", name);
		len = -ENXIO;
		goto out_attach;
	}

	WARN_ON_ONCE(!is_nvdimm_bus_locked(dev));
	if (!__nd_attach_ndns(dev, ndns, _ndns)) {
		dev_dbg(dev, "%s already claimed\n",
				dev_name(&ndns->dev));
		len = -EBUSY;
	}

 out_attach:
	put_device(&ndns->dev); /* from device_find_child */
 out:
	kfree(name);
	return len;
}