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
typedef  int /*<<< orphan*/  kvm_pfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
 int /*<<< orphan*/  kvm_is_reserved_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_is_zone_device_pfn (int /*<<< orphan*/ ) ; 
 struct page* pfn_to_page (int /*<<< orphan*/ ) ; 

void kvm_set_pfn_dirty(kvm_pfn_t pfn)
{
	if (!kvm_is_reserved_pfn(pfn) && !kvm_is_zone_device_pfn(pfn)) {
		struct page *page = pfn_to_page(pfn);

		SetPageDirty(page);
	}
}