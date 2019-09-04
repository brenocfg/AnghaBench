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
struct nfs4_state {int /*<<< orphan*/  seqlock; int /*<<< orphan*/  open_stateid; int /*<<< orphan*/  stateid; int /*<<< orphan*/  flags; } ;
struct nfs4_opendata {int dummy; } ;

/* Variables and functions */
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  NFS_DELEGATED_STATE ; 
 int /*<<< orphan*/  NFS_OPEN_STATE ; 
 int /*<<< orphan*/  NFS_O_RDONLY_STATE ; 
 int /*<<< orphan*/  NFS_O_RDWR_STATE ; 
 int /*<<< orphan*/  NFS_O_WRONLY_STATE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nfs4_open_recover_helper (struct nfs4_opendata*,int) ; 
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_stateid_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs4_open_recover(struct nfs4_opendata *opendata, struct nfs4_state *state)
{
	int ret;

	/* Don't trigger recovery in nfs_test_and_clear_all_open_stateid */
	clear_bit(NFS_O_RDWR_STATE, &state->flags);
	clear_bit(NFS_O_WRONLY_STATE, &state->flags);
	clear_bit(NFS_O_RDONLY_STATE, &state->flags);
	/* memory barrier prior to reading state->n_* */
	clear_bit(NFS_DELEGATED_STATE, &state->flags);
	clear_bit(NFS_OPEN_STATE, &state->flags);
	smp_rmb();
	ret = nfs4_open_recover_helper(opendata, FMODE_READ|FMODE_WRITE);
	if (ret != 0)
		return ret;
	ret = nfs4_open_recover_helper(opendata, FMODE_WRITE);
	if (ret != 0)
		return ret;
	ret = nfs4_open_recover_helper(opendata, FMODE_READ);
	if (ret != 0)
		return ret;
	/*
	 * We may have performed cached opens for all three recoveries.
	 * Check if we need to update the current stateid.
	 */
	if (test_bit(NFS_DELEGATED_STATE, &state->flags) == 0 &&
	    !nfs4_stateid_match(&state->stateid, &state->open_stateid)) {
		write_seqlock(&state->seqlock);
		if (test_bit(NFS_DELEGATED_STATE, &state->flags) == 0)
			nfs4_stateid_copy(&state->stateid, &state->open_stateid);
		write_sequnlock(&state->seqlock);
	}
	return 0;
}