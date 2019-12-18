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
struct nfs_server {int /*<<< orphan*/  lockowner_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner_id; } ;
struct nfs4_lock_state {TYPE_1__ ls_seqid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfs4_lock_state*) ; 
 int /*<<< orphan*/  nfs4_destroy_seqid_counter (TYPE_1__*) ; 

void nfs4_free_lock_state(struct nfs_server *server, struct nfs4_lock_state *lsp)
{
	ida_simple_remove(&server->lockowner_id, lsp->ls_seqid.owner_id);
	nfs4_destroy_seqid_counter(&lsp->ls_seqid);
	kfree(lsp);
}