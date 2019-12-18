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
struct nfs_server {struct nfs_client* nfs_client; } ;
struct nfs_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs4_schedule_state_manager (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs4_wait_clnt_recover (struct nfs_client*) ; 
 int nfs_server_mark_return_all_delegations (struct nfs_server*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void nfs_server_return_all_delegations(struct nfs_server *server)
{
	struct nfs_client *clp = server->nfs_client;
	bool need_wait;

	if (clp == NULL)
		return;

	rcu_read_lock();
	need_wait = nfs_server_mark_return_all_delegations(server);
	rcu_read_unlock();

	if (need_wait) {
		nfs4_schedule_state_manager(clp);
		nfs4_wait_clnt_recover(clp);
	}
}