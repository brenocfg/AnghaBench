#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  seqid; } ;
struct nfs4_state {TYPE_1__ open_stateid; int /*<<< orphan*/  seqlock; } ;
struct TYPE_6__ {int /*<<< orphan*/  seqid; } ;
typedef  TYPE_2__ nfs4_stateid ;

/* Variables and functions */
 scalar_t__ nfs4_state_match_open_stateid_other (struct nfs4_state*,TYPE_2__*) ; 
 int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,int) ; 

bool nfs4_refresh_open_stateid(nfs4_stateid *dst, struct nfs4_state *state)
{
	bool ret;
	int seq;

	do {
		ret = false;
		seq = read_seqbegin(&state->seqlock);
		if (nfs4_state_match_open_stateid_other(state, dst)) {
			dst->seqid = state->open_stateid.seqid;
			ret = true;
		}
	} while (read_seqretry(&state->seqlock, seq));
	return ret;
}