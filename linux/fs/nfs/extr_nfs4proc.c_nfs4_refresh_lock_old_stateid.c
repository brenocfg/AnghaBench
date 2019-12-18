#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct nfs4_state {int /*<<< orphan*/  state_lock; } ;
struct TYPE_9__ {int /*<<< orphan*/  seqid; } ;
struct nfs4_lock_state {TYPE_4__ ls_stateid; struct nfs4_state* ls_state; } ;
struct TYPE_8__ {int /*<<< orphan*/  seqid; } ;
typedef  TYPE_1__ nfs4_stateid ;

/* Variables and functions */
 int /*<<< orphan*/  nfs4_stateid_is_newer (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  nfs4_stateid_match_other (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  nfs4_stateid_seqid_inc (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nfs4_refresh_lock_old_stateid(nfs4_stateid *dst,
		struct nfs4_lock_state *lsp)
{
	struct nfs4_state *state = lsp->ls_state;
	bool ret = false;

	spin_lock(&state->state_lock);
	if (!nfs4_stateid_match_other(dst, &lsp->ls_stateid))
		goto out;
	if (!nfs4_stateid_is_newer(&lsp->ls_stateid, dst))
		nfs4_stateid_seqid_inc(dst);
	else
		dst->seqid = lsp->ls_stateid.seqid;
	ret = true;
out:
	spin_unlock(&state->state_lock);
	return ret;
}