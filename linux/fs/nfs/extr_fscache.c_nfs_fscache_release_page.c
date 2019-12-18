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
struct page {TYPE_1__* mapping; } ;
struct fscache_cookie {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  FSCACHE ; 
 int /*<<< orphan*/  NFSIOS_FSCACHE_PAGES_UNCACHED ; 
 int /*<<< orphan*/  NFS_I (int /*<<< orphan*/ ) ; 
 scalar_t__ PageFsCache (struct page*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct fscache_cookie*,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscache_maybe_release_page (struct fscache_cookie*,struct page*,int /*<<< orphan*/ ) ; 
 struct fscache_cookie* nfs_i_fscache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_inc_fscache_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nfs_fscache_release_page(struct page *page, gfp_t gfp)
{
	if (PageFsCache(page)) {
		struct fscache_cookie *cookie = nfs_i_fscache(page->mapping->host);

		BUG_ON(!cookie);
		dfprintk(FSCACHE, "NFS: fscache releasepage (0x%p/0x%p/0x%p)\n",
			 cookie, page, NFS_I(page->mapping->host));

		if (!fscache_maybe_release_page(cookie, page, gfp))
			return 0;

		nfs_inc_fscache_stats(page->mapping->host,
				      NFSIOS_FSCACHE_PAGES_UNCACHED);
	}

	return 1;
}