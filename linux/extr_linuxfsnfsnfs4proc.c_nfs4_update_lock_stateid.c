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
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nfs4_stateid_is_newer (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_stateid_match_other (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nfs4_update_lock_stateid(struct nfs4_lock_state *lsp,
		const nfs4_stateid *stateid)
{
	struct nfs4_state *state = lsp->ls_state;
	bool ret = false;

	spin_lock(&state->state_lock);
	if (!nfs4_stateid_match_other(stateid, &lsp->ls_stateid))
		goto out_noupdate;
	if (!nfs4_stateid_is_newer(stateid, &lsp->ls_stateid))
		goto out_noupdate;
	nfs4_stateid_copy(&lsp->ls_stateid, stateid);
	ret = true;
out_noupdate:
	spin_unlock(&state->state_lock);
	return ret;
}