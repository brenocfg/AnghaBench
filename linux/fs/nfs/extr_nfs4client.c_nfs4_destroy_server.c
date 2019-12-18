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
struct nfs_server {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeme ; 
 int /*<<< orphan*/  nfs4_free_state_owners (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_purge_state_owners (struct nfs_server*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_server_return_all_delegations (struct nfs_server*) ; 
 int /*<<< orphan*/  unset_pnfs_layoutdriver (struct nfs_server*) ; 

__attribute__((used)) static void nfs4_destroy_server(struct nfs_server *server)
{
	LIST_HEAD(freeme);

	nfs_server_return_all_delegations(server);
	unset_pnfs_layoutdriver(server);
	nfs4_purge_state_owners(server, &freeme);
	nfs4_free_state_owners(&freeme);
}