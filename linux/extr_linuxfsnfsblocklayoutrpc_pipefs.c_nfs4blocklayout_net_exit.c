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
struct nfs_net {int /*<<< orphan*/ * bl_device_pipe; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct nfs_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4blocklayout_unregister_net (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_net_id ; 
 int /*<<< orphan*/  rpc_destroy_pipe_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs4blocklayout_net_exit(struct net *net)
{
	struct nfs_net *nn = net_generic(net, nfs_net_id);

	nfs4blocklayout_unregister_net(net, nn->bl_device_pipe);
	rpc_destroy_pipe_data(nn->bl_device_pipe);
	nn->bl_device_pipe = NULL;
}