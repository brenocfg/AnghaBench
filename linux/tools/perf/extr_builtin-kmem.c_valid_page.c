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
typedef  unsigned long u64 ;

/* Variables and functions */
 scalar_t__ use_pfn ; 

__attribute__((used)) static bool valid_page(u64 pfn_or_page)
{
	if (use_pfn && pfn_or_page == -1UL)
		return false;
	if (!use_pfn && pfn_or_page == 0)
		return false;
	return true;
}