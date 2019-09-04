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
 int __add_to_page_cache_locked (struct page*,struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int add_to_page_cache_locked(struct page *page, struct address_space *mapping,
		pgoff_t offset, gfp_t gfp_mask)
{
	return __add_to_page_cache_locked(page, mapping, offset,
					  gfp_mask, NULL);
}