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
struct nfs_server {int /*<<< orphan*/  cred; int /*<<< orphan*/  io_stats; int /*<<< orphan*/  openowner_id; int /*<<< orphan*/  lockowner_id; int /*<<< orphan*/  nfs_client; int /*<<< orphan*/  client; int /*<<< orphan*/  client_acl; int /*<<< orphan*/  (* destroy ) (struct nfs_server*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nfs_server*) ; 
 int /*<<< orphan*/  nfs_free_iostats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_put_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_release_automount_timer () ; 
 int /*<<< orphan*/  nfs_server_remove_lists (struct nfs_server*) ; 
 int /*<<< orphan*/  put_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_shutdown_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nfs_server*) ; 

void nfs_free_server(struct nfs_server *server)
{
	nfs_server_remove_lists(server);

	if (server->destroy != NULL)
		server->destroy(server);

	if (!IS_ERR(server->client_acl))
		rpc_shutdown_client(server->client_acl);
	if (!IS_ERR(server->client))
		rpc_shutdown_client(server->client);

	nfs_put_client(server->nfs_client);

	ida_destroy(&server->lockowner_id);
	ida_destroy(&server->openowner_id);
	nfs_free_iostats(server->io_stats);
	put_cred(server->cred);
	kfree(server);
	nfs_release_automount_timer();
}