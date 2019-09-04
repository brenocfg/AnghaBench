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
typedef  unsigned int u64 ;
struct pfn_array {unsigned int pa_nr; unsigned int* pa_iova_pfn; unsigned int pa_iova; unsigned int* pa_pfn; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IOMMU_READ ; 
 int IOMMU_WRITE ; 
 unsigned int PAGE_MASK ; 
 unsigned int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 unsigned int* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (unsigned int*) ; 
 scalar_t__ unlikely (int) ; 
 int vfio_pin_pages (struct device*,unsigned int*,int,int,unsigned int*) ; 
 int /*<<< orphan*/  vfio_unpin_pages (struct device*,unsigned int*,int) ; 

__attribute__((used)) static int pfn_array_alloc_pin(struct pfn_array *pa, struct device *mdev,
			       u64 iova, unsigned int len)
{
	int i, ret = 0;

	if (!len)
		return 0;

	if (pa->pa_nr || pa->pa_iova_pfn)
		return -EINVAL;

	pa->pa_iova = iova;

	pa->pa_nr = ((iova & ~PAGE_MASK) + len + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	if (!pa->pa_nr)
		return -EINVAL;

	pa->pa_iova_pfn = kcalloc(pa->pa_nr,
				  sizeof(*pa->pa_iova_pfn) +
				  sizeof(*pa->pa_pfn),
				  GFP_KERNEL);
	if (unlikely(!pa->pa_iova_pfn))
		return -ENOMEM;
	pa->pa_pfn = pa->pa_iova_pfn + pa->pa_nr;

	pa->pa_iova_pfn[0] = pa->pa_iova >> PAGE_SHIFT;
	for (i = 1; i < pa->pa_nr; i++)
		pa->pa_iova_pfn[i] = pa->pa_iova_pfn[i - 1] + 1;

	ret = vfio_pin_pages(mdev, pa->pa_iova_pfn, pa->pa_nr,
			     IOMMU_READ | IOMMU_WRITE, pa->pa_pfn);

	if (ret < 0) {
		goto err_out;
	} else if (ret > 0 && ret != pa->pa_nr) {
		vfio_unpin_pages(mdev, pa->pa_iova_pfn, ret);
		ret = -EINVAL;
		goto err_out;
	}

	return ret;

err_out:
	pa->pa_nr = 0;
	kfree(pa->pa_iova_pfn);
	pa->pa_iova_pfn = NULL;

	return ret;
}