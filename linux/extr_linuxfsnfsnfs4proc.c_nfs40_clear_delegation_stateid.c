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
struct nfs4_state {int /*<<< orphan*/  inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  delegation; } ;

/* Variables and functions */
 TYPE_1__* NFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_finish_clear_delegation_stateid (struct nfs4_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rcu_access_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs40_clear_delegation_stateid(struct nfs4_state *state)
{
	if (rcu_access_pointer(NFS_I(state->inode)->delegation) != NULL)
		nfs_finish_clear_delegation_stateid(state, NULL);
}