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
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rpcs_out; } ;
struct nfs_inode {TYPE_1__ commit_info; } ;
struct address_space {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 struct nfs_inode* NFS_I (int /*<<< orphan*/ ) ; 
 scalar_t__ PagePrivate (struct page*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct address_space* page_file_mapping (struct page*) ; 

__attribute__((used)) static void nfs_check_dirty_writeback(struct page *page,
				bool *dirty, bool *writeback)
{
	struct nfs_inode *nfsi;
	struct address_space *mapping = page_file_mapping(page);

	if (!mapping || PageSwapCache(page))
		return;

	/*
	 * Check if an unstable page is currently being committed and
	 * if so, have the VM treat it as if the page is under writeback
	 * so it will not block due to pages that will shortly be freeable.
	 */
	nfsi = NFS_I(mapping->host);
	if (atomic_read(&nfsi->commit_info.rpcs_out)) {
		*writeback = true;
		return;
	}

	/*
	 * If PagePrivate() is set, then the page is not freeable and as the
	 * inode is not being committed, it's not going to be cleaned in the
	 * near future so treat it as dirty
	 */
	if (PagePrivate(page))
		*dirty = true;
}