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
struct nfs_inode {int cache_validity; int /*<<< orphan*/  access_cache_entry_lru; } ;
struct nfs_access_entry {int /*<<< orphan*/  lru; int /*<<< orphan*/  mask; int /*<<< orphan*/  cred; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int ECHILD ; 
 int ENOENT ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int NFS_INO_INVALID_ACCESS ; 
 int /*<<< orphan*/  NFS_SERVER (struct inode*) ; 
 int __nfs_revalidate_inode (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nfs_access_entry* nfs_access_search_rbtree (struct inode*,struct cred const*) ; 
 int /*<<< orphan*/  nfs_access_zap_cache (struct inode*) ; 
 int /*<<< orphan*/  nfs_check_cache_invalid (struct inode*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs_access_get_cached(struct inode *inode, const struct cred *cred, struct nfs_access_entry *res, bool may_block)
{
	struct nfs_inode *nfsi = NFS_I(inode);
	struct nfs_access_entry *cache;
	bool retry = true;
	int err;

	spin_lock(&inode->i_lock);
	for(;;) {
		if (nfsi->cache_validity & NFS_INO_INVALID_ACCESS)
			goto out_zap;
		cache = nfs_access_search_rbtree(inode, cred);
		err = -ENOENT;
		if (cache == NULL)
			goto out;
		/* Found an entry, is our attribute cache valid? */
		if (!nfs_check_cache_invalid(inode, NFS_INO_INVALID_ACCESS))
			break;
		err = -ECHILD;
		if (!may_block)
			goto out;
		if (!retry)
			goto out_zap;
		spin_unlock(&inode->i_lock);
		err = __nfs_revalidate_inode(NFS_SERVER(inode), inode);
		if (err)
			return err;
		spin_lock(&inode->i_lock);
		retry = false;
	}
	res->cred = cache->cred;
	res->mask = cache->mask;
	list_move_tail(&cache->lru, &nfsi->access_cache_entry_lru);
	err = 0;
out:
	spin_unlock(&inode->i_lock);
	return err;
out_zap:
	spin_unlock(&inode->i_lock);
	nfs_access_zap_cache(inode);
	return -ENOENT;
}