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
struct nfs_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs4_state_mark_reclaim_helper (struct nfs_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_state_mark_reclaim_reboot ; 
 int /*<<< orphan*/  nfs_delegation_mark_reclaim (struct nfs_client*) ; 

__attribute__((used)) static void nfs4_state_start_reclaim_reboot(struct nfs_client *clp)
{
	/* Mark all delegations for reclaim */
	nfs_delegation_mark_reclaim(clp);
	nfs4_state_mark_reclaim_helper(clp, nfs4_state_mark_reclaim_reboot);
}