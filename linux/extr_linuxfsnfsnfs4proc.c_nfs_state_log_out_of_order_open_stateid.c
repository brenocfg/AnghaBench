#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  seqid; } ;
struct nfs4_state {int /*<<< orphan*/  flags; TYPE_1__ open_stateid; } ;
struct TYPE_5__ {int /*<<< orphan*/  seqid; } ;
typedef  TYPE_2__ nfs4_stateid ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_STATE_CHANGE_WAIT ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_state_log_update_open_stateid (struct nfs4_state*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_state_log_out_of_order_open_stateid(struct nfs4_state *state,
		const nfs4_stateid *stateid)
{
	u32 state_seqid = be32_to_cpu(state->open_stateid.seqid);
	u32 stateid_seqid = be32_to_cpu(stateid->seqid);

	if (stateid_seqid == state_seqid + 1U ||
	    (stateid_seqid == 1U && state_seqid == 0xffffffffU))
		nfs_state_log_update_open_stateid(state);
	else
		set_bit(NFS_STATE_CHANGE_WAIT, &state->flags);
}