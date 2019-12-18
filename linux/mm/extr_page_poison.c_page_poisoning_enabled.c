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

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ARCH_SUPPORTS_DEBUG_PAGEALLOC ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ debug_pagealloc_enabled () ; 
 scalar_t__ want_page_poisoning ; 

bool page_poisoning_enabled(void)
{
	/*
	 * Assumes that debug_pagealloc_enabled is set before
	 * memblock_free_all.
	 * Page poisoning is debug page alloc for some arches. If
	 * either of those options are enabled, enable poisoning.
	 */
	return (want_page_poisoning ||
		(!IS_ENABLED(CONFIG_ARCH_SUPPORTS_DEBUG_PAGEALLOC) &&
		debug_pagealloc_enabled()));
}