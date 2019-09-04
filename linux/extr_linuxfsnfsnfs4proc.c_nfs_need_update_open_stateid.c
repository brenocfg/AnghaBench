#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nfs4_state {int /*<<< orphan*/  open_stateid; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {scalar_t__ seqid; } ;
typedef  TYPE_1__ nfs4_stateid ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_OPEN_STATE ; 
 int /*<<< orphan*/  NFS_STATE_CHANGE_WAIT ; 
 scalar_t__ cpu_to_be32 (int) ; 
 scalar_t__ nfs4_stateid_is_newer (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_stateid_match_other (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_state_log_out_of_order_open_stateid (struct nfs4_state*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  nfs_state_log_update_open_stateid (struct nfs4_state*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nfs_need_update_open_stateid(struct nfs4_state *state,
		const nfs4_stateid *stateid)
{
	if (test_bit(NFS_OPEN_STATE, &state->flags) == 0 ||
	    !nfs4_stateid_match_other(stateid, &state->open_stateid)) {
		if (stateid->seqid == cpu_to_be32(1))
			nfs_state_log_update_open_stateid(state);
		else
			set_bit(NFS_STATE_CHANGE_WAIT, &state->flags);
		return true;
	}

	if (nfs4_stateid_is_newer(stateid, &state->open_stateid)) {
		nfs_state_log_out_of_order_open_stateid(state, stateid);
		return true;
	}
	return false;
}