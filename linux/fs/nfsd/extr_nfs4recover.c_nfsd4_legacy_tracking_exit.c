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
struct nfsd_net {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_legacy_state_shutdown (struct net*) ; 
 int /*<<< orphan*/  nfs4_release_reclaim (struct nfsd_net*) ; 
 int /*<<< orphan*/  nfsd4_shutdown_recdir (struct net*) ; 
 int /*<<< orphan*/  nfsd_net_id ; 

__attribute__((used)) static void
nfsd4_legacy_tracking_exit(struct net *net)
{
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);

	nfs4_release_reclaim(nn);
	nfsd4_shutdown_recdir(net);
	nfs4_legacy_state_shutdown(net);
}