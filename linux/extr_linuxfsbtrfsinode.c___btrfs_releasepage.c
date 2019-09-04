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
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 
 int try_release_extent_mapping (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __btrfs_releasepage(struct page *page, gfp_t gfp_flags)
{
	int ret = try_release_extent_mapping(page, gfp_flags);
	if (ret == 1) {
		ClearPagePrivate(page);
		set_page_private(page, 0);
		put_page(page);
	}
	return ret;
}