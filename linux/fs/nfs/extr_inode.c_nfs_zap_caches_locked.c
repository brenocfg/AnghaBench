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
struct nfs_inode {int /*<<< orphan*/  cookieverf; int /*<<< orphan*/  attrtimeo_timestamp; int /*<<< orphan*/  attrtimeo; } ;
struct inode {int i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSIOS_ATTRINVALIDATE ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int NFS_INO_INVALID_ACCESS ; 
 int NFS_INO_INVALID_ACL ; 
 int NFS_INO_INVALID_ATTR ; 
 int NFS_INO_INVALID_DATA ; 
 int NFS_INO_REVAL_PAGECACHE ; 
 int /*<<< orphan*/  NFS_MINATTRTIMEO (struct inode*) ; 
 scalar_t__ S_ISDIR (int) ; 
 scalar_t__ S_ISLNK (int) ; 
 scalar_t__ S_ISREG (int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_set_cache_invalid (struct inode*,int) ; 
 int /*<<< orphan*/  nfs_zap_label_cache_locked (struct nfs_inode*) ; 

__attribute__((used)) static void nfs_zap_caches_locked(struct inode *inode)
{
	struct nfs_inode *nfsi = NFS_I(inode);
	int mode = inode->i_mode;

	nfs_inc_stats(inode, NFSIOS_ATTRINVALIDATE);

	nfsi->attrtimeo = NFS_MINATTRTIMEO(inode);
	nfsi->attrtimeo_timestamp = jiffies;

	memset(NFS_I(inode)->cookieverf, 0, sizeof(NFS_I(inode)->cookieverf));
	if (S_ISREG(mode) || S_ISDIR(mode) || S_ISLNK(mode)) {
		nfs_set_cache_invalid(inode, NFS_INO_INVALID_ATTR
					| NFS_INO_INVALID_DATA
					| NFS_INO_INVALID_ACCESS
					| NFS_INO_INVALID_ACL
					| NFS_INO_REVAL_PAGECACHE);
	} else
		nfs_set_cache_invalid(inode, NFS_INO_INVALID_ATTR
					| NFS_INO_INVALID_ACCESS
					| NFS_INO_INVALID_ACL
					| NFS_INO_REVAL_PAGECACHE);
	nfs_zap_label_cache_locked(nfsi);
}