#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_emu10k1 {int iommu_workaround; TYPE_1__* card; } ;
struct iommu_domain {scalar_t__ type; } ;
struct TYPE_5__ {int /*<<< orphan*/  bus; } ;
struct TYPE_4__ {TYPE_2__* dev; } ;

/* Variables and functions */
 scalar_t__ IOMMU_DOMAIN_IDENTITY ; 
 int /*<<< orphan*/  dev_notice (TYPE_2__*,char*) ; 
 struct iommu_domain* iommu_get_domain_for_dev (TYPE_2__*) ; 
 int /*<<< orphan*/  iommu_present (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_emu10k1_detect_iommu(struct snd_emu10k1 *emu)
{
	struct iommu_domain *domain;

	emu->iommu_workaround = false;

	if (!iommu_present(emu->card->dev->bus))
		return;

	domain = iommu_get_domain_for_dev(emu->card->dev);
	if (domain && domain->type == IOMMU_DOMAIN_IDENTITY)
		return;

	dev_notice(emu->card->dev,
		   "non-passthrough IOMMU detected, widening DMA allocations");
	emu->iommu_workaround = true;
}