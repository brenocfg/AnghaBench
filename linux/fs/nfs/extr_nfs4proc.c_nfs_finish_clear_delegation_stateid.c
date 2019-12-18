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
struct nfs4_state {int /*<<< orphan*/  inode; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_remove_bad_delegation (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nfs_state_clear_delegation (struct nfs4_state*) ; 

__attribute__((used)) static void nfs_finish_clear_delegation_stateid(struct nfs4_state *state,
		const nfs4_stateid *stateid)
{
	nfs_remove_bad_delegation(state->inode, stateid);
	nfs_state_clear_delegation(state);
}