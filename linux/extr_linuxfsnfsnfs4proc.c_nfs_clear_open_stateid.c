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
struct nfs4_state {TYPE_2__* owner; int /*<<< orphan*/  flags; int /*<<< orphan*/  seqlock; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_4__ {TYPE_1__* so_server; } ;
struct TYPE_3__ {int /*<<< orphan*/  nfs_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_STATE_RECLAIM_NOGRACE ; 
 int /*<<< orphan*/  nfs4_schedule_state_manager (int /*<<< orphan*/ ) ; 
 scalar_t__ nfs4_state_match_open_stateid_other (struct nfs4_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_clear_open_stateid_locked (struct nfs4_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_clear_open_stateid(struct nfs4_state *state,
	nfs4_stateid *arg_stateid,
	nfs4_stateid *stateid, fmode_t fmode)
{
	write_seqlock(&state->seqlock);
	/* Ignore, if the CLOSE argment doesn't match the current stateid */
	if (nfs4_state_match_open_stateid_other(state, arg_stateid))
		nfs_clear_open_stateid_locked(state, stateid, fmode);
	write_sequnlock(&state->seqlock);
	if (test_bit(NFS_STATE_RECLAIM_NOGRACE, &state->flags))
		nfs4_schedule_state_manager(state->owner->so_server->nfs_client);
}