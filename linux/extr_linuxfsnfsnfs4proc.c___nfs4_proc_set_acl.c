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
struct rpc_message {struct nfs_setaclres* rpc_resp; struct nfs_setaclargs* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct page {int dummy; } ;
struct nfs_setaclres {int /*<<< orphan*/  seq_res; } ;
struct nfs_setaclargs {size_t acl_len; int /*<<< orphan*/  seq_args; struct page** acl_pages; int /*<<< orphan*/  fh; } ;
struct nfs_server {int /*<<< orphan*/  client; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
struct TYPE_2__ {int cache_validity; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct page**) ; 
 unsigned int DIV_ROUND_UP (size_t,int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
 int ERANGE ; 
 int NFS4ACL_MAXPAGES ; 
 size_t NFSPROC4_CLNT_SETACL ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 TYPE_1__* NFS_I (struct inode*) ; 
 int NFS_INO_INVALID_CHANGE ; 
 int NFS_INO_INVALID_CTIME ; 
 int NFS_INO_REVAL_FORCED ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int buf_to_pages_noslab (void const*,size_t,struct page**) ; 
 int nfs4_call_sync (int /*<<< orphan*/ ,struct nfs_server*,struct rpc_message*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfs4_inode_make_writeable (struct inode*) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  nfs4_server_supports_acls (struct nfs_server*) ; 
 int /*<<< orphan*/  nfs_access_zap_cache (struct inode*) ; 
 int /*<<< orphan*/  nfs_zap_acl_cache (struct inode*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __nfs4_proc_set_acl(struct inode *inode, const void *buf, size_t buflen)
{
	struct nfs_server *server = NFS_SERVER(inode);
	struct page *pages[NFS4ACL_MAXPAGES];
	struct nfs_setaclargs arg = {
		.fh		= NFS_FH(inode),
		.acl_pages	= pages,
		.acl_len	= buflen,
	};
	struct nfs_setaclres res;
	struct rpc_message msg = {
		.rpc_proc	= &nfs4_procedures[NFSPROC4_CLNT_SETACL],
		.rpc_argp	= &arg,
		.rpc_resp	= &res,
	};
	unsigned int npages = DIV_ROUND_UP(buflen, PAGE_SIZE);
	int ret, i;

	if (!nfs4_server_supports_acls(server))
		return -EOPNOTSUPP;
	if (npages > ARRAY_SIZE(pages))
		return -ERANGE;
	i = buf_to_pages_noslab(buf, buflen, arg.acl_pages);
	if (i < 0)
		return i;
	nfs4_inode_make_writeable(inode);
	ret = nfs4_call_sync(server->client, server, &msg, &arg.seq_args, &res.seq_res, 1);

	/*
	 * Free each page after tx, so the only ref left is
	 * held by the network stack
	 */
	for (; i > 0; i--)
		put_page(pages[i-1]);

	/*
	 * Acl update can result in inode attribute update.
	 * so mark the attribute cache invalid.
	 */
	spin_lock(&inode->i_lock);
	NFS_I(inode)->cache_validity |= NFS_INO_INVALID_CHANGE
		| NFS_INO_INVALID_CTIME
		| NFS_INO_REVAL_FORCED;
	spin_unlock(&inode->i_lock);
	nfs_access_zap_cache(inode);
	nfs_zap_acl_cache(inode);
	return ret;
}