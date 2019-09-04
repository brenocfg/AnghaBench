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
struct nfs_inode {int cache_validity; int /*<<< orphan*/  flags; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct nfs_inode* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_INO_INVALIDATING ; 
 int NFS_INO_INVALID_DATA ; 
 int NFS_INO_REVAL_PAGECACHE ; 
 scalar_t__ PageUptodate (struct page*) ; 
 scalar_t__ nfs_have_delegated_attributes (struct inode*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nfs_write_pageuptodate(struct page *page, struct inode *inode)
{
	struct nfs_inode *nfsi = NFS_I(inode);

	if (nfs_have_delegated_attributes(inode))
		goto out;
	if (nfsi->cache_validity & NFS_INO_REVAL_PAGECACHE)
		return false;
	smp_rmb();
	if (test_bit(NFS_INO_INVALIDATING, &nfsi->flags))
		return false;
out:
	if (nfsi->cache_validity & NFS_INO_INVALID_DATA)
		return false;
	return PageUptodate(page) != 0;
}