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
 int /*<<< orphan*/  PAGECACHE ; 
 scalar_t__ PagePrivate (struct page*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct page*) ; 
 int nfs_fscache_release_page (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs_release_page(struct page *page, gfp_t gfp)
{
	dfprintk(PAGECACHE, "NFS: release_page(%p)\n", page);

	/* If PagePrivate() is set, then the page is not freeable */
	if (PagePrivate(page))
		return 0;
	return nfs_fscache_release_page(page, gfp);
}