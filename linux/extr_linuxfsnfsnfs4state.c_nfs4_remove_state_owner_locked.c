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
struct nfs_server {int /*<<< orphan*/  state_owners; } ;
struct nfs4_state_owner {int /*<<< orphan*/  so_server_node; struct nfs_server* so_server; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfs4_remove_state_owner_locked(struct nfs4_state_owner *sp)
{
	struct nfs_server *server = sp->so_server;

	if (!RB_EMPTY_NODE(&sp->so_server_node))
		rb_erase(&sp->so_server_node, &server->state_owners);
}