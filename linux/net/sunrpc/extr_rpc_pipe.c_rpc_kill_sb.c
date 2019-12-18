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
struct super_block {struct net* s_fs_info; } ;
struct sunrpc_net {int /*<<< orphan*/  pipefs_sb_lock; struct super_block* pipefs_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  inum; } ;
struct net {TYPE_1__ ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_NAME (struct net*) ; 
 int /*<<< orphan*/  RPC_PIPEFS_UMOUNT ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct super_block*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_litter_super (struct super_block*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sunrpc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_net (struct net*) ; 
 int /*<<< orphan*/  rpc_pipefs_notifier_list ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

__attribute__((used)) static void rpc_kill_sb(struct super_block *sb)
{
	struct net *net = sb->s_fs_info;
	struct sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	mutex_lock(&sn->pipefs_sb_lock);
	if (sn->pipefs_sb != sb) {
		mutex_unlock(&sn->pipefs_sb_lock);
		goto out;
	}
	sn->pipefs_sb = NULL;
	dprintk("RPC:       sending pipefs UMOUNT notification for net %x%s\n",
		net->ns.inum, NET_NAME(net));
	blocking_notifier_call_chain(&rpc_pipefs_notifier_list,
					   RPC_PIPEFS_UMOUNT,
					   sb);
	mutex_unlock(&sn->pipefs_sb_lock);
out:
	kill_litter_super(sb);
	put_net(net);
}