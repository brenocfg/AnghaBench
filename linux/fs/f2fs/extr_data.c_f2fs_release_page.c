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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ IS_ATOMIC_WRITTEN_PAGE (struct page*) ; 
 scalar_t__ PageDirty (struct page*) ; 
 int /*<<< orphan*/  clear_cold_data (struct page*) ; 
 int /*<<< orphan*/  f2fs_clear_page_private (struct page*) ; 

int f2fs_release_page(struct page *page, gfp_t wait)
{
	/* If this is dirty page, keep PagePrivate */
	if (PageDirty(page))
		return 0;

	/* This is atomic written page, keep Private */
	if (IS_ATOMIC_WRITTEN_PAGE(page))
		return 0;

	clear_cold_data(page);
	f2fs_clear_page_private(page);
	return 1;
}