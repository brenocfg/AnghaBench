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
struct nfs_client {int /*<<< orphan*/  cl_state; } ;
struct nfs4_state {TYPE_1__* owner; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  so_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4CLNT_RECLAIM_REBOOT ; 
 int /*<<< orphan*/  NFS_OWNER_RECLAIM_REBOOT ; 
 int /*<<< orphan*/  NFS_STATE_RECLAIM_NOGRACE ; 
 int /*<<< orphan*/  NFS_STATE_RECLAIM_REBOOT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_valid_open_stateid (struct nfs4_state*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs4_state_mark_reclaim_reboot(struct nfs_client *clp, struct nfs4_state *state)
{

	if (!nfs4_valid_open_stateid(state))
		return 0;
	set_bit(NFS_STATE_RECLAIM_REBOOT, &state->flags);
	/* Don't recover state that expired before the reboot */
	if (test_bit(NFS_STATE_RECLAIM_NOGRACE, &state->flags)) {
		clear_bit(NFS_STATE_RECLAIM_REBOOT, &state->flags);
		return 0;
	}
	set_bit(NFS_OWNER_RECLAIM_REBOOT, &state->owner->so_flags);
	set_bit(NFS4CLNT_RECLAIM_REBOOT, &clp->cl_state);
	return 1;
}