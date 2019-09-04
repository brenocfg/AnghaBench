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
 unsigned int AOP_FLAG_NOFS ; 
 int FGP_CREAT ; 
 int FGP_LOCK ; 
 int FGP_NOFS ; 
 int FGP_WRITE ; 
 int /*<<< orphan*/  mapping_gfp_mask (struct address_space*) ; 
 struct page* pagecache_get_page (struct address_space*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_stable_page (struct page*) ; 

struct page *grab_cache_page_write_begin(struct address_space *mapping,
					pgoff_t index, unsigned flags)
{
	struct page *page;
	int fgp_flags = FGP_LOCK|FGP_WRITE|FGP_CREAT;

	if (flags & AOP_FLAG_NOFS)
		fgp_flags |= FGP_NOFS;

	page = pagecache_get_page(mapping, index, fgp_flags,
			mapping_gfp_mask(mapping));
	if (page)
		wait_for_stable_page(page);

	return page;
}