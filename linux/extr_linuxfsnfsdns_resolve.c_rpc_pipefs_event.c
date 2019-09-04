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
struct super_block {struct net* s_fs_info; } ;
struct notifier_block {int dummy; } ;
struct nfs_net {struct cache_detail* nfs_dns_resolve; } ;
struct net {int dummy; } ;
struct cache_detail {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  RPC_PIPEFS_MOUNT 129 
#define  RPC_PIPEFS_UMOUNT 128 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct nfs_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int nfs_cache_register_sb (struct super_block*,struct cache_detail*) ; 
 int /*<<< orphan*/  nfs_cache_unregister_sb (struct super_block*,struct cache_detail*) ; 
 int /*<<< orphan*/  nfs_net_id ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpc_pipefs_event(struct notifier_block *nb, unsigned long event,
			   void *ptr)
{
	struct super_block *sb = ptr;
	struct net *net = sb->s_fs_info;
	struct nfs_net *nn = net_generic(net, nfs_net_id);
	struct cache_detail *cd = nn->nfs_dns_resolve;
	int ret = 0;

	if (cd == NULL)
		return 0;

	if (!try_module_get(THIS_MODULE))
		return 0;

	switch (event) {
	case RPC_PIPEFS_MOUNT:
		ret = nfs_cache_register_sb(sb, cd);
		break;
	case RPC_PIPEFS_UMOUNT:
		nfs_cache_unregister_sb(sb, cd);
		break;
	default:
		ret = -ENOTSUPP;
		break;
	}
	module_put(THIS_MODULE);
	return ret;
}