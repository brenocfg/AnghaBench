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
struct nfs4_state {int /*<<< orphan*/  state_lock; } ;
struct nfs4_lock_state {int /*<<< orphan*/  ls_stateid; struct nfs4_state* ls_state; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;

/* Variables and functions */
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_stateid_match_other (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nfs4_sync_lock_stateid(nfs4_stateid *dst,
		struct nfs4_lock_state *lsp)
{
	struct nfs4_state *state = lsp->ls_state;
	bool ret;

	spin_lock(&state->state_lock);
	ret = !nfs4_stateid_match_other(dst, &lsp->ls_stateid);
	nfs4_stateid_copy(dst, &lsp->ls_stateid);
	spin_unlock(&state->state_lock);
	return ret;
}