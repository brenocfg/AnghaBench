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
struct kvm_vcpu {int dummy; } ;
struct kvm_host_map {int /*<<< orphan*/ * page; int /*<<< orphan*/ * hva; int /*<<< orphan*/  pfn; int /*<<< orphan*/  gfn; } ;

/* Variables and functions */
 int /*<<< orphan*/ * KVM_UNMAPPED_PAGE ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_release_pfn_clean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_release_pfn_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vcpu_mark_page_dirty (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memunmap (int /*<<< orphan*/ *) ; 

void kvm_vcpu_unmap(struct kvm_vcpu *vcpu, struct kvm_host_map *map,
		    bool dirty)
{
	if (!map)
		return;

	if (!map->hva)
		return;

	if (map->page != KVM_UNMAPPED_PAGE)
		kunmap(map->page);
#ifdef CONFIG_HAS_IOMEM
	else
		memunmap(map->hva);
#endif

	if (dirty) {
		kvm_vcpu_mark_page_dirty(vcpu, map->gfn);
		kvm_release_pfn_dirty(map->pfn);
	} else {
		kvm_release_pfn_clean(map->pfn);
	}

	map->hva = NULL;
	map->page = NULL;
}