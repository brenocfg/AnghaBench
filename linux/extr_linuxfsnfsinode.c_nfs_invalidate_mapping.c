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
struct nfs_inode {int /*<<< orphan*/  cookieverf; } ;
struct inode {TYPE_1__* i_sb; int /*<<< orphan*/  i_lock; int /*<<< orphan*/  i_mode; } ;
struct address_space {scalar_t__ nrpages; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSIOS_DATAINVALIDATE ; 
 scalar_t__ NFS_FILEID (struct inode*) ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  PAGECACHE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int invalidate_inode_pages2 (struct address_space*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_fscache_wait_on_invalidate (struct inode*) ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 
 int nfs_sync_mapping (struct address_space*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs_invalidate_mapping(struct inode *inode, struct address_space *mapping)
{
	struct nfs_inode *nfsi = NFS_I(inode);
	int ret;

	if (mapping->nrpages != 0) {
		if (S_ISREG(inode->i_mode)) {
			ret = nfs_sync_mapping(mapping);
			if (ret < 0)
				return ret;
		}
		ret = invalidate_inode_pages2(mapping);
		if (ret < 0)
			return ret;
	}
	if (S_ISDIR(inode->i_mode)) {
		spin_lock(&inode->i_lock);
		memset(nfsi->cookieverf, 0, sizeof(nfsi->cookieverf));
		spin_unlock(&inode->i_lock);
	}
	nfs_inc_stats(inode, NFSIOS_DATAINVALIDATE);
	nfs_fscache_wait_on_invalidate(inode);

	dfprintk(PAGECACHE, "NFS: (%s/%Lu) data cache invalidated\n",
			inode->i_sb->s_id,
			(unsigned long long)NFS_FILEID(inode));
	return 0;
}