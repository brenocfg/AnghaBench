#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int /*<<< orphan*/  index; TYPE_1__* mapping; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 scalar_t__ PageDirty (struct page*) ; 
 int /*<<< orphan*/  PagePrivate (struct page*) ; 
 int /*<<< orphan*/  ceph_release_fscache_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ceph_releasepage(struct page *page, gfp_t g)
{
	dout("%p releasepage %p idx %lu (%sdirty)\n", page->mapping->host,
	     page, page->index, PageDirty(page) ? "" : "not ");

	/* Can we release the page from the cache? */
	if (!ceph_release_fscache_page(page, g))
		return 0;

	return !PagePrivate(page);
}