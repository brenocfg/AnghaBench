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
struct device {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ IS_ERR (struct nd_namespace_common*) ; 
 int PTR_ERR (struct nd_namespace_common*) ; 
 scalar_t__ devm_nsio_enable (struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_nd_btt (struct device*) ; 
 scalar_t__ is_nd_pfn (struct device*) ; 
 scalar_t__ nd_btt_probe (struct device*,struct nd_namespace_common*) ; 
 scalar_t__ nd_dax_probe (struct device*,struct nd_namespace_common*) ; 
 scalar_t__ nd_pfn_probe (struct device*,struct nd_namespace_common*) ; 
 int nvdimm_namespace_attach_btt (struct nd_namespace_common*) ; 
 struct nd_namespace_common* nvdimm_namespace_common_probe (struct device*) ; 
 int pmem_attach_disk (struct device*,struct nd_namespace_common*) ; 
 int /*<<< orphan*/  to_nd_namespace_io (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nd_pmem_probe(struct device *dev)
{
	struct nd_namespace_common *ndns;

	ndns = nvdimm_namespace_common_probe(dev);
	if (IS_ERR(ndns))
		return PTR_ERR(ndns);

	if (devm_nsio_enable(dev, to_nd_namespace_io(&ndns->dev)))
		return -ENXIO;

	if (is_nd_btt(dev))
		return nvdimm_namespace_attach_btt(ndns);

	if (is_nd_pfn(dev))
		return pmem_attach_disk(dev, ndns);

	/* if we find a valid info-block we'll come back as that personality */
	if (nd_btt_probe(dev, ndns) == 0 || nd_pfn_probe(dev, ndns) == 0
			|| nd_dax_probe(dev, ndns) == 0)
		return -ENXIO;

	/* ...otherwise we're just a raw pmem device */
	return pmem_attach_disk(dev, ndns);
}