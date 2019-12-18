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
struct page {int dummy; } ;
struct kvm_memory_slot {int dummy; } ;
struct kvm_host_map {int /*<<< orphan*/  gfn; int /*<<< orphan*/  pfn; void* hva; struct page* page; } ;
typedef  int /*<<< orphan*/  kvm_pfn_t ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 struct page* KVM_UNMAPPED_PAGE ; 
 int /*<<< orphan*/  MEMREMAP_WB ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  gfn_to_pfn_memslot (struct kvm_memory_slot*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_error_noslot_pfn (int /*<<< orphan*/ ) ; 
 void* kmap (struct page*) ; 
 void* memremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_to_hpa (int /*<<< orphan*/ ) ; 
 struct page* pfn_to_page (int /*<<< orphan*/ ) ; 
 scalar_t__ pfn_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __kvm_map_gfn(struct kvm_memory_slot *slot, gfn_t gfn,
			 struct kvm_host_map *map)
{
	kvm_pfn_t pfn;
	void *hva = NULL;
	struct page *page = KVM_UNMAPPED_PAGE;

	if (!map)
		return -EINVAL;

	pfn = gfn_to_pfn_memslot(slot, gfn);
	if (is_error_noslot_pfn(pfn))
		return -EINVAL;

	if (pfn_valid(pfn)) {
		page = pfn_to_page(pfn);
		hva = kmap(page);
#ifdef CONFIG_HAS_IOMEM
	} else {
		hva = memremap(pfn_to_hpa(pfn), PAGE_SIZE, MEMREMAP_WB);
#endif
	}

	if (!hva)
		return -EFAULT;

	map->page = page;
	map->hva = hva;
	map->pfn = pfn;
	map->gfn = gfn;

	return 0;
}