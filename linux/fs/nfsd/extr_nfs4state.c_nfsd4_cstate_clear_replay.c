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
struct nfsd4_compound_state {struct nfs4_stateowner* replay_owner; } ;
struct TYPE_2__ {int /*<<< orphan*/  rp_mutex; } ;
struct nfs4_stateowner {TYPE_1__ so_replay; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_put_stateowner (struct nfs4_stateowner*) ; 

void nfsd4_cstate_clear_replay(struct nfsd4_compound_state *cstate)
{
	struct nfs4_stateowner *so = cstate->replay_owner;

	if (so != NULL) {
		cstate->replay_owner = NULL;
		mutex_unlock(&so->so_replay.rp_mutex);
		nfs4_put_stateowner(so);
	}
}