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
struct nfsd_net {int nfsd_net_up; scalar_t__ lockd_up; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockd_down (struct net*) ; 
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_state_shutdown_net (struct net*) ; 
 int /*<<< orphan*/  nfsd_file_cache_purge (struct net*) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  nfsd_shutdown_generic () ; 

__attribute__((used)) static void nfsd_shutdown_net(struct net *net)
{
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);

	nfsd_file_cache_purge(net);
	nfs4_state_shutdown_net(net);
	if (nn->lockd_up) {
		lockd_down(net);
		nn->lockd_up = 0;
	}
	nn->nfsd_net_up = false;
	nfsd_shutdown_generic();
}