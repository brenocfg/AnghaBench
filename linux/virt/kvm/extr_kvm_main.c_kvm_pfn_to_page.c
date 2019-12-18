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
 struct page* KVM_ERR_PTR_BAD_PAGE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ is_error_noslot_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_is_reserved_pfn (int /*<<< orphan*/ ) ; 
 struct page* pfn_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct page *kvm_pfn_to_page(kvm_pfn_t pfn)
{
	if (is_error_noslot_pfn(pfn))
		return KVM_ERR_PTR_BAD_PAGE;

	if (kvm_is_reserved_pfn(pfn)) {
		WARN_ON(1);
		return KVM_ERR_PTR_BAD_PAGE;
	}

	return pfn_to_page(pfn);
}