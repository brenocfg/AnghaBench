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
struct seq_file {int dummy; } ;
struct nfs_server {TYPE_1__* nfs_client; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  cl_rpcclient; } ;

/* Variables and functions */
 struct nfs_server* NFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_DISPLAY_ADDR ; 
 int /*<<< orphan*/  nfs_show_mount_options (struct seq_file*,struct nfs_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rpc_peeraddr2str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

int nfs_show_options(struct seq_file *m, struct dentry *root)
{
	struct nfs_server *nfss = NFS_SB(root->d_sb);

	nfs_show_mount_options(m, nfss, 0);

	rcu_read_lock();
	seq_printf(m, ",addr=%s",
			rpc_peeraddr2str(nfss->nfs_client->cl_rpcclient,
							RPC_DISPLAY_ADDR));
	rcu_read_unlock();

	return 0;
}