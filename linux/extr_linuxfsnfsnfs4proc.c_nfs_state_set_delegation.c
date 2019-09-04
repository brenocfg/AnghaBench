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
struct nfs4_state {int /*<<< orphan*/  seqlock; int /*<<< orphan*/  flags; int /*<<< orphan*/  stateid; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_DELEGATED_STATE ; 
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_state_set_delegation(struct nfs4_state *state,
		const nfs4_stateid *deleg_stateid,
		fmode_t fmode)
{
	/*
	 * Protect the call to nfs4_state_set_mode_locked and
	 * serialise the stateid update
	 */
	write_seqlock(&state->seqlock);
	nfs4_stateid_copy(&state->stateid, deleg_stateid);
	set_bit(NFS_DELEGATED_STATE, &state->flags);
	write_sequnlock(&state->seqlock);
}