#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfs_server {int dummy; } ;
struct nfs_inode {int cache_validity; int /*<<< orphan*/  flags; } ;
struct nfs_fattr {int dummy; } ;
struct nfs4_label {int dummy; } ;
struct inode {TYPE_1__* i_sb; int /*<<< orphan*/  i_mode; } ;
struct TYPE_4__ {int (* getattr ) (struct nfs_server*,int /*<<< orphan*/ ,struct nfs_fattr*,struct nfs4_label*,struct inode*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ESTALE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct nfs4_label*) ; 
 int /*<<< orphan*/  NFSIOS_INODEREVALIDATE ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 scalar_t__ NFS_FILEID (struct inode*) ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int NFS_INO_INVALID_ACL ; 
 int /*<<< orphan*/  NFS_INO_STALE ; 
 TYPE_2__* NFS_PROTO (struct inode*) ; 
 int /*<<< orphan*/  NFS_SERVER (struct inode*) ; 
 scalar_t__ NFS_STALE (struct inode*) ; 
 int /*<<< orphan*/  PAGECACHE ; 
 int PTR_ERR (struct nfs4_label*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned long long,...) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 struct nfs4_label* nfs4_label_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_label_free (struct nfs4_label*) ; 
 struct nfs_fattr* nfs_alloc_fattr () ; 
 int /*<<< orphan*/  nfs_free_fattr (struct nfs_fattr*) ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 
 int nfs_refresh_inode (struct inode*,struct nfs_fattr*) ; 
 int /*<<< orphan*/  nfs_setsecurity (struct inode*,struct nfs_fattr*,struct nfs4_label*) ; 
 int /*<<< orphan*/  nfs_zap_acl_cache (struct inode*) ; 
 int /*<<< orphan*/  nfs_zap_caches (struct inode*) ; 
 int pnfs_sync_inode (struct inode*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct nfs_server*,int /*<<< orphan*/ ,struct nfs_fattr*,struct nfs4_label*,struct inode*) ; 
 int /*<<< orphan*/  trace_nfs_revalidate_inode_enter (struct inode*) ; 
 int /*<<< orphan*/  trace_nfs_revalidate_inode_exit (struct inode*,int) ; 

int
__nfs_revalidate_inode(struct nfs_server *server, struct inode *inode)
{
	int		 status = -ESTALE;
	struct nfs4_label *label = NULL;
	struct nfs_fattr *fattr = NULL;
	struct nfs_inode *nfsi = NFS_I(inode);

	dfprintk(PAGECACHE, "NFS: revalidating (%s/%Lu)\n",
		inode->i_sb->s_id, (unsigned long long)NFS_FILEID(inode));

	trace_nfs_revalidate_inode_enter(inode);

	if (is_bad_inode(inode))
		goto out;
	if (NFS_STALE(inode))
		goto out;

	/* pNFS: Attributes aren't updated until we layoutcommit */
	if (S_ISREG(inode->i_mode)) {
		status = pnfs_sync_inode(inode, false);
		if (status)
			goto out;
	}

	status = -ENOMEM;
	fattr = nfs_alloc_fattr();
	if (fattr == NULL)
		goto out;

	nfs_inc_stats(inode, NFSIOS_INODEREVALIDATE);

	label = nfs4_label_alloc(NFS_SERVER(inode), GFP_KERNEL);
	if (IS_ERR(label)) {
		status = PTR_ERR(label);
		goto out;
	}

	status = NFS_PROTO(inode)->getattr(server, NFS_FH(inode), fattr,
			label, inode);
	if (status != 0) {
		dfprintk(PAGECACHE, "nfs_revalidate_inode: (%s/%Lu) getattr failed, error=%d\n",
			 inode->i_sb->s_id,
			 (unsigned long long)NFS_FILEID(inode), status);
		if (status == -ESTALE) {
			nfs_zap_caches(inode);
			if (!S_ISDIR(inode->i_mode))
				set_bit(NFS_INO_STALE, &NFS_I(inode)->flags);
		}
		goto err_out;
	}

	status = nfs_refresh_inode(inode, fattr);
	if (status) {
		dfprintk(PAGECACHE, "nfs_revalidate_inode: (%s/%Lu) refresh failed, error=%d\n",
			 inode->i_sb->s_id,
			 (unsigned long long)NFS_FILEID(inode), status);
		goto err_out;
	}

	if (nfsi->cache_validity & NFS_INO_INVALID_ACL)
		nfs_zap_acl_cache(inode);

	nfs_setsecurity(inode, fattr, label);

	dfprintk(PAGECACHE, "NFS: (%s/%Lu) revalidation complete\n",
		inode->i_sb->s_id,
		(unsigned long long)NFS_FILEID(inode));

err_out:
	nfs4_label_free(label);
out:
	nfs_free_fattr(fattr);
	trace_nfs_revalidate_inode_exit(inode, status);
	return status;
}