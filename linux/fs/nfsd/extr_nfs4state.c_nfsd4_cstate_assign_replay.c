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
struct nfsd4_compound_state {int /*<<< orphan*/  replay_owner; } ;
struct TYPE_2__ {int /*<<< orphan*/  rp_mutex; } ;
struct nfs4_stateowner {TYPE_1__ so_replay; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_get_stateowner (struct nfs4_stateowner*) ; 
 int /*<<< orphan*/  nfsd4_has_session (struct nfsd4_compound_state*) ; 

__attribute__((used)) static void nfsd4_cstate_assign_replay(struct nfsd4_compound_state *cstate,
		struct nfs4_stateowner *so)
{
	if (!nfsd4_has_session(cstate)) {
		mutex_lock(&so->so_replay.rp_mutex);
		cstate->replay_owner = nfs4_get_stateowner(so);
	}
}