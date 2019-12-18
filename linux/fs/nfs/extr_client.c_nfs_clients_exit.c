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
struct nfs_net {int /*<<< orphan*/  nfs_volume_list; int /*<<< orphan*/  nfs_client_list; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct nfs_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_cleanup_cb_ident_idr (struct net*) ; 
 int /*<<< orphan*/  nfs_net_id ; 
 int /*<<< orphan*/  nfs_netns_sysfs_destroy (struct nfs_net*) ; 

void nfs_clients_exit(struct net *net)
{
	struct nfs_net *nn = net_generic(net, nfs_net_id);

	nfs_netns_sysfs_destroy(nn);
	nfs_cleanup_cb_ident_idr(net);
	WARN_ON_ONCE(!list_empty(&nn->nfs_client_list));
	WARN_ON_ONCE(!list_empty(&nn->nfs_volume_list));
}