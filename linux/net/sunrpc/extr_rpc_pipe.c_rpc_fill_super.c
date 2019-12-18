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
struct super_block {int s_time_gran; struct dentry* s_root; int /*<<< orphan*/ * s_d_op; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_blocksize; struct net* s_fs_info; } ;
struct sunrpc_net {int /*<<< orphan*/  pipefs_sb_lock; struct super_block* pipefs_sb; int /*<<< orphan*/  gssd_dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  inum; } ;
struct net {TYPE_1__ ns; } ;
struct inode {int dummy; } ;
struct fs_context {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  NET_NAME (struct net*) ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  RPCAUTH_GSSMAGIC ; 
 int /*<<< orphan*/  RPCAUTH_RootEOF ; 
 int /*<<< orphan*/  RPCAUTH_lockd ; 
 int /*<<< orphan*/  RPC_PIPEFS_MOUNT ; 
 int /*<<< orphan*/  RPC_PIPEFS_UMOUNT ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  __rpc_depopulate (struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct super_block*) ; 
 struct dentry* d_make_root (struct inode*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  files ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sunrpc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct inode* rpc_get_inode (struct super_block*,int) ; 
 int /*<<< orphan*/  rpc_gssd_dummy_depopulate (struct dentry*) ; 
 struct dentry* rpc_gssd_dummy_populate (struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_pipefs_notifier_list ; 
 scalar_t__ rpc_populate (struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_ops ; 
 int /*<<< orphan*/  simple_dentry_operations ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

__attribute__((used)) static int
rpc_fill_super(struct super_block *sb, struct fs_context *fc)
{
	struct inode *inode;
	struct dentry *root, *gssd_dentry;
	struct net *net = sb->s_fs_info;
	struct sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	int err;

	sb->s_blocksize = PAGE_SIZE;
	sb->s_blocksize_bits = PAGE_SHIFT;
	sb->s_magic = RPCAUTH_GSSMAGIC;
	sb->s_op = &s_ops;
	sb->s_d_op = &simple_dentry_operations;
	sb->s_time_gran = 1;

	inode = rpc_get_inode(sb, S_IFDIR | 0555);
	sb->s_root = root = d_make_root(inode);
	if (!root)
		return -ENOMEM;
	if (rpc_populate(root, files, RPCAUTH_lockd, RPCAUTH_RootEOF, NULL))
		return -ENOMEM;

	gssd_dentry = rpc_gssd_dummy_populate(root, sn->gssd_dummy);
	if (IS_ERR(gssd_dentry)) {
		__rpc_depopulate(root, files, RPCAUTH_lockd, RPCAUTH_RootEOF);
		return PTR_ERR(gssd_dentry);
	}

	dprintk("RPC:       sending pipefs MOUNT notification for net %x%s\n",
		net->ns.inum, NET_NAME(net));
	mutex_lock(&sn->pipefs_sb_lock);
	sn->pipefs_sb = sb;
	err = blocking_notifier_call_chain(&rpc_pipefs_notifier_list,
					   RPC_PIPEFS_MOUNT,
					   sb);
	if (err)
		goto err_depopulate;
	mutex_unlock(&sn->pipefs_sb_lock);
	return 0;

err_depopulate:
	rpc_gssd_dummy_depopulate(gssd_dentry);
	blocking_notifier_call_chain(&rpc_pipefs_notifier_list,
					   RPC_PIPEFS_UMOUNT,
					   sb);
	sn->pipefs_sb = NULL;
	__rpc_depopulate(root, files, RPCAUTH_lockd, RPCAUTH_RootEOF);
	mutex_unlock(&sn->pipefs_sb_lock);
	return err;
}