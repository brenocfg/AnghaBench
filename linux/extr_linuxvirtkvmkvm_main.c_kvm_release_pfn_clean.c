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
typedef  int /*<<< orphan*/  kvm_pfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  is_error_noslot_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_is_reserved_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_to_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

void kvm_release_pfn_clean(kvm_pfn_t pfn)
{
	if (!is_error_noslot_pfn(pfn) && !kvm_is_reserved_pfn(pfn))
		put_page(pfn_to_page(pfn));
}