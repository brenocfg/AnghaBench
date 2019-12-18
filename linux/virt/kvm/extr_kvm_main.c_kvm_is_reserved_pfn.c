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
 scalar_t__ PageReserved (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_is_zone_device_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_to_page (int /*<<< orphan*/ ) ; 
 scalar_t__ pfn_valid (int /*<<< orphan*/ ) ; 

bool kvm_is_reserved_pfn(kvm_pfn_t pfn)
{
	/*
	 * ZONE_DEVICE pages currently set PG_reserved, but from a refcounting
	 * perspective they are "normal" pages, albeit with slightly different
	 * usage rules.
	 */
	if (pfn_valid(pfn))
		return PageReserved(pfn_to_page(pfn)) &&
		       !kvm_is_zone_device_pfn(pfn);

	return true;
}