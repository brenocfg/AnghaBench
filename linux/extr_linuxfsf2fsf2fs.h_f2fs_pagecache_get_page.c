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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_M_SB (struct address_space*) ; 
 int /*<<< orphan*/  FAULT_PAGE_GET ; 
 int /*<<< orphan*/  f2fs_show_injection_info (int /*<<< orphan*/ ) ; 
 struct page* pagecache_get_page (struct address_space*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ time_to_inject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct page *f2fs_pagecache_get_page(
				struct address_space *mapping, pgoff_t index,
				int fgp_flags, gfp_t gfp_mask)
{
	if (time_to_inject(F2FS_M_SB(mapping), FAULT_PAGE_GET)) {
		f2fs_show_injection_info(FAULT_PAGE_GET);
		return NULL;
	}

	return pagecache_get_page(mapping, index, fgp_flags, gfp_mask);
}