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
struct TYPE_2__ {struct device* parent; } ;
struct rproc {struct iommu_domain* domain; int /*<<< orphan*/  has_iommu; TYPE_1__ dev; } ;
struct iommu_domain {int dummy; } ;
struct device {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int iommu_attach_device (struct iommu_domain*,struct device*) ; 
 struct iommu_domain* iommu_domain_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_domain_free (struct iommu_domain*) ; 
 int /*<<< orphan*/  iommu_set_fault_handler (struct iommu_domain*,int /*<<< orphan*/ ,struct rproc*) ; 
 int /*<<< orphan*/  rproc_iommu_fault ; 

__attribute__((used)) static int rproc_enable_iommu(struct rproc *rproc)
{
	struct iommu_domain *domain;
	struct device *dev = rproc->dev.parent;
	int ret;

	if (!rproc->has_iommu) {
		dev_dbg(dev, "iommu not present\n");
		return 0;
	}

	domain = iommu_domain_alloc(dev->bus);
	if (!domain) {
		dev_err(dev, "can't alloc iommu domain\n");
		return -ENOMEM;
	}

	iommu_set_fault_handler(domain, rproc_iommu_fault, rproc);

	ret = iommu_attach_device(domain, dev);
	if (ret) {
		dev_err(dev, "can't attach iommu device: %d\n", ret);
		goto free_domain;
	}

	rproc->domain = domain;

	return 0;

free_domain:
	iommu_domain_free(domain);
	return ret;
}