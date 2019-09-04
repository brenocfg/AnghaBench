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
struct nfs4_state {int /*<<< orphan*/  seqlock; int /*<<< orphan*/  flags; int /*<<< orphan*/  open_stateid; int /*<<< orphan*/  stateid; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_DELEGATED_STATE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_state_clear_delegation(struct nfs4_state *state)
{
	write_seqlock(&state->seqlock);
	nfs4_stateid_copy(&state->stateid, &state->open_stateid);
	clear_bit(NFS_DELEGATED_STATE, &state->flags);
	write_sequnlock(&state->seqlock);
}