#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  owner_id; } ;
struct nfs4_state_owner {TYPE_2__ so_seqid; TYPE_1__* so_server; int /*<<< orphan*/  so_cred; } ;
struct TYPE_3__ {int /*<<< orphan*/  openowner_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfs4_state_owner*) ; 
 int /*<<< orphan*/  nfs4_destroy_seqid_counter (TYPE_2__*) ; 
 int /*<<< orphan*/  put_cred (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs4_free_state_owner(struct nfs4_state_owner *sp)
{
	nfs4_destroy_seqid_counter(&sp->so_seqid);
	put_cred(sp->so_cred);
	ida_simple_remove(&sp->so_server->openowner_id, sp->so_seqid.owner_id);
	kfree(sp);
}