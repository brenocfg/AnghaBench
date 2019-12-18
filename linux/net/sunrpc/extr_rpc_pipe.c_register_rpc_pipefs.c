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
struct rpc_inode {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int SLAB_ACCOUNT ; 
 int SLAB_HWCACHE_ALIGN ; 
 int SLAB_MEM_SPREAD ; 
 int SLAB_RECLAIM_ACCOUNT ; 
 int /*<<< orphan*/  init_once ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int register_filesystem (int /*<<< orphan*/ *) ; 
 int rpc_clients_notifier_register () ; 
 int /*<<< orphan*/  rpc_clients_notifier_unregister () ; 
 int /*<<< orphan*/  rpc_inode_cachep ; 
 int /*<<< orphan*/  rpc_pipe_fs_type ; 

int register_rpc_pipefs(void)
{
	int err;

	rpc_inode_cachep = kmem_cache_create("rpc_inode_cache",
				sizeof(struct rpc_inode),
				0, (SLAB_HWCACHE_ALIGN|SLAB_RECLAIM_ACCOUNT|
						SLAB_MEM_SPREAD|SLAB_ACCOUNT),
				init_once);
	if (!rpc_inode_cachep)
		return -ENOMEM;
	err = rpc_clients_notifier_register();
	if (err)
		goto err_notifier;
	err = register_filesystem(&rpc_pipe_fs_type);
	if (err)
		goto err_register;
	return 0;

err_register:
	rpc_clients_notifier_unregister();
err_notifier:
	kmem_cache_destroy(rpc_inode_cachep);
	return err;
}