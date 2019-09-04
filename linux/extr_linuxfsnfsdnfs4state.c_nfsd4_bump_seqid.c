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
struct nfsd4_compound_state {struct nfs4_stateowner* replay_owner; } ;
struct nfs4_stateowner {int /*<<< orphan*/  so_seqid; scalar_t__ so_is_open_owner; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  nfsd4_cstate_clear_replay (struct nfsd4_compound_state*) ; 
 scalar_t__ nfserr_replay_me ; 
 int /*<<< orphan*/  ntohl (scalar_t__) ; 
 int /*<<< orphan*/  openowner (struct nfs4_stateowner*) ; 
 int /*<<< orphan*/  release_last_closed_stateid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seqid_mutating_err (int /*<<< orphan*/ ) ; 

void nfsd4_bump_seqid(struct nfsd4_compound_state *cstate, __be32 nfserr)
{
	struct nfs4_stateowner *so = cstate->replay_owner;

	if (nfserr == nfserr_replay_me)
		return;

	if (!seqid_mutating_err(ntohl(nfserr))) {
		nfsd4_cstate_clear_replay(cstate);
		return;
	}
	if (!so)
		return;
	if (so->so_is_open_owner)
		release_last_closed_stateid(openowner(so));
	so->so_seqid++;
	return;
}