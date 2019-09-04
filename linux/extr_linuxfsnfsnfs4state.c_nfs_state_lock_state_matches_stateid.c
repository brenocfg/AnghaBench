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
struct nfs4_state {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;

/* Variables and functions */
 int /*<<< orphan*/  LK_STATE_IN_USE ; 
 scalar_t__ nfs_state_find_lock_state_by_stateid (struct nfs4_state*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nfs_state_lock_state_matches_stateid(struct nfs4_state *state,
		const nfs4_stateid *stateid)
{
	bool found = false;

	if (test_bit(LK_STATE_IN_USE, &state->flags)) {
		spin_lock(&state->state_lock);
		if (nfs_state_find_lock_state_by_stateid(state, stateid))
			found = true;
		spin_unlock(&state->state_lock);
	}
	return found;
}