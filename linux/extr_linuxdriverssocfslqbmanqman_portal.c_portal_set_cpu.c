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
struct qm_portal_config {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  qman_set_sdest (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void portal_set_cpu(struct qm_portal_config *pcfg, int cpu)
{
#ifdef CONFIG_FSL_PAMU
	struct device *dev = pcfg->dev;
	int window_count = 1;
	struct iommu_domain_geometry geom_attr;
	struct pamu_stash_attribute stash_attr;
	int ret;

	pcfg->iommu_domain = iommu_domain_alloc(&platform_bus_type);
	if (!pcfg->iommu_domain) {
		dev_err(dev, "%s(): iommu_domain_alloc() failed", __func__);
		goto no_iommu;
	}
	geom_attr.aperture_start = 0;
	geom_attr.aperture_end =
		((dma_addr_t)1 << min(8 * sizeof(dma_addr_t), (size_t)36)) - 1;
	geom_attr.force_aperture = true;
	ret = iommu_domain_set_attr(pcfg->iommu_domain, DOMAIN_ATTR_GEOMETRY,
				    &geom_attr);
	if (ret < 0) {
		dev_err(dev, "%s(): iommu_domain_set_attr() = %d", __func__,
			ret);
		goto out_domain_free;
	}
	ret = iommu_domain_set_attr(pcfg->iommu_domain, DOMAIN_ATTR_WINDOWS,
				    &window_count);
	if (ret < 0) {
		dev_err(dev, "%s(): iommu_domain_set_attr() = %d", __func__,
			ret);
		goto out_domain_free;
	}
	stash_attr.cpu = cpu;
	stash_attr.cache = PAMU_ATTR_CACHE_L1;
	ret = iommu_domain_set_attr(pcfg->iommu_domain,
				    DOMAIN_ATTR_FSL_PAMU_STASH,
				    &stash_attr);
	if (ret < 0) {
		dev_err(dev, "%s(): iommu_domain_set_attr() = %d",
			__func__, ret);
		goto out_domain_free;
	}
	ret = iommu_domain_window_enable(pcfg->iommu_domain, 0, 0, 1ULL << 36,
					 IOMMU_READ | IOMMU_WRITE);
	if (ret < 0) {
		dev_err(dev, "%s(): iommu_domain_window_enable() = %d",
			__func__, ret);
		goto out_domain_free;
	}
	ret = iommu_attach_device(pcfg->iommu_domain, dev);
	if (ret < 0) {
		dev_err(dev, "%s(): iommu_device_attach() = %d", __func__,
			ret);
		goto out_domain_free;
	}
	ret = iommu_domain_set_attr(pcfg->iommu_domain,
				    DOMAIN_ATTR_FSL_PAMU_ENABLE,
				    &window_count);
	if (ret < 0) {
		dev_err(dev, "%s(): iommu_domain_set_attr() = %d", __func__,
			ret);
		goto out_detach_device;
	}

no_iommu:
#endif
	qman_set_sdest(pcfg->channel, cpu);

	return;

#ifdef CONFIG_FSL_PAMU
out_detach_device:
	iommu_detach_device(pcfg->iommu_domain, NULL);
out_domain_free:
	iommu_domain_free(pcfg->iommu_domain);
	pcfg->iommu_domain = NULL;
#endif
}