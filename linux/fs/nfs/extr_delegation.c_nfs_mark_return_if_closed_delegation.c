#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfs_server {TYPE_1__* nfs_client; } ;
struct nfs_delegation {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  cl_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4CLNT_DELEGRETURN ; 
 int /*<<< orphan*/  NFS_DELEGATION_RETURN_IF_CLOSED ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_mark_return_if_closed_delegation(struct nfs_server *server,
		struct nfs_delegation *delegation)
{
	set_bit(NFS_DELEGATION_RETURN_IF_CLOSED, &delegation->flags);
	set_bit(NFS4CLNT_DELEGRETURN, &server->nfs_client->cl_state);
}