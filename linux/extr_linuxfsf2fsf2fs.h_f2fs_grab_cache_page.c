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
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOP_FLAG_NOFS ; 
 int /*<<< orphan*/  CONFIG_F2FS_FAULT_INJECTION ; 
 int /*<<< orphan*/  F2FS_M_SB (struct address_space*) ; 
 int /*<<< orphan*/  FAULT_PAGE_ALLOC ; 
 int FGP_ACCESSED ; 
 int FGP_LOCK ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_show_injection_info (int /*<<< orphan*/ ) ; 
 struct page* find_get_page_flags (struct address_space*,int /*<<< orphan*/ ,int) ; 
 struct page* find_lock_page (struct address_space*,int /*<<< orphan*/ ) ; 
 struct page* grab_cache_page (struct address_space*,int /*<<< orphan*/ ) ; 
 struct page* grab_cache_page_write_begin (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_to_inject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct page *f2fs_grab_cache_page(struct address_space *mapping,
						pgoff_t index, bool for_write)
{
	struct page *page;

	if (IS_ENABLED(CONFIG_F2FS_FAULT_INJECTION)) {
		if (!for_write)
			page = find_get_page_flags(mapping, index,
							FGP_LOCK | FGP_ACCESSED);
		else
			page = find_lock_page(mapping, index);
		if (page)
			return page;

		if (time_to_inject(F2FS_M_SB(mapping), FAULT_PAGE_ALLOC)) {
			f2fs_show_injection_info(FAULT_PAGE_ALLOC);
			return NULL;
		}
	}

	if (!for_write)
		return grab_cache_page(mapping, index);
	return grab_cache_page_write_begin(mapping, index, AOP_FLAG_NOFS);
}