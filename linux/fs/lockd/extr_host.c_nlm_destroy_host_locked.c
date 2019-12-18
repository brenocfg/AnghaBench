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
struct rpc_clnt {int dummy; } ;
struct nlm_host {int /*<<< orphan*/  h_cred; struct rpc_clnt* h_rpcclnt; int /*<<< orphan*/  h_nsmhandle; int /*<<< orphan*/  h_hash; int /*<<< orphan*/  h_name; int /*<<< orphan*/  net; } ;
struct lockd_net {int /*<<< orphan*/  nrhosts; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nlm_host*) ; 
 int /*<<< orphan*/  lockd_net_id ; 
 struct lockd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nrhosts ; 
 int /*<<< orphan*/  nsm_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsm_unmonitor (struct nlm_host*) ; 
 int /*<<< orphan*/  put_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_shutdown_client (struct rpc_clnt*) ; 

__attribute__((used)) static void nlm_destroy_host_locked(struct nlm_host *host)
{
	struct rpc_clnt	*clnt;
	struct lockd_net *ln = net_generic(host->net, lockd_net_id);

	dprintk("lockd: destroy host %s\n", host->h_name);

	hlist_del_init(&host->h_hash);

	nsm_unmonitor(host);
	nsm_release(host->h_nsmhandle);

	clnt = host->h_rpcclnt;
	if (clnt != NULL)
		rpc_shutdown_client(clnt);
	put_cred(host->h_cred);
	kfree(host);

	ln->nrhosts--;
	nrhosts--;
}