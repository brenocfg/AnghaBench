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
 scalar_t__ WARN_ON_ONCE (int) ; 
 int is_zone_device_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_to_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_valid (int /*<<< orphan*/ ) ; 

bool kvm_is_zone_device_pfn(kvm_pfn_t pfn)
{
	/*
	 * The metadata used by is_zone_device_page() to determine whether or
	 * not a page is ZONE_DEVICE is guaranteed to be valid if and only if
	 * the device has been pinned, e.g. by get_user_pages().  WARN if the
	 * page_count() is zero to help detect bad usage of this helper.
	 */
	if (!pfn_valid(pfn) || WARN_ON_ONCE(!page_count(pfn_to_page(pfn))))
		return false;

	return is_zone_device_page(pfn_to_page(pfn));
}