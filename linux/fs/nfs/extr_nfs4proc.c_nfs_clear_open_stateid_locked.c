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
struct nfs4_state {int /*<<< orphan*/  inode; int /*<<< orphan*/  open_stateid; int /*<<< orphan*/  stateid; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;
typedef  int fmode_t ;

/* Variables and functions */
#define  FMODE_READ 129 
#define  FMODE_WRITE 128 
 int /*<<< orphan*/  NFS_DELEGATED_STATE ; 
 int /*<<< orphan*/  NFS_OPEN_STATE ; 
 int /*<<< orphan*/  NFS_O_RDONLY_STATE ; 
 int /*<<< orphan*/  NFS_O_RDWR_STATE ; 
 int /*<<< orphan*/  NFS_O_WRONLY_STATE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_stateid_is_newer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nfs4_stateid_match_other (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_resync_open_stateid_locked (struct nfs4_state*) ; 
 int /*<<< orphan*/  nfs_state_log_update_open_stateid (struct nfs4_state*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_nfs4_open_stateid_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs_clear_open_stateid_locked(struct nfs4_state *state,
		nfs4_stateid *stateid, fmode_t fmode)
{
	clear_bit(NFS_O_RDWR_STATE, &state->flags);
	switch (fmode & (FMODE_READ|FMODE_WRITE)) {
	case FMODE_WRITE:
		clear_bit(NFS_O_RDONLY_STATE, &state->flags);
		break;
	case FMODE_READ:
		clear_bit(NFS_O_WRONLY_STATE, &state->flags);
		break;
	case 0:
		clear_bit(NFS_O_RDONLY_STATE, &state->flags);
		clear_bit(NFS_O_WRONLY_STATE, &state->flags);
		clear_bit(NFS_OPEN_STATE, &state->flags);
	}
	if (stateid == NULL)
		return;
	/* Handle OPEN+OPEN_DOWNGRADE races */
	if (nfs4_stateid_match_other(stateid, &state->open_stateid) &&
	    !nfs4_stateid_is_newer(stateid, &state->open_stateid)) {
		nfs_resync_open_stateid_locked(state);
		goto out;
	}
	if (test_bit(NFS_DELEGATED_STATE, &state->flags) == 0)
		nfs4_stateid_copy(&state->stateid, stateid);
	nfs4_stateid_copy(&state->open_stateid, stateid);
	trace_nfs4_open_stateid_update(state->inode, stateid, 0);
out:
	nfs_state_log_update_open_stateid(state);
}