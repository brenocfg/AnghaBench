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
struct nfs4_delegation {int /*<<< orphan*/  dl_stid; int /*<<< orphan*/  dl_clnt_odstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs4_put_stid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_unlock_deleg_lease (struct nfs4_delegation*) ; 
 int /*<<< orphan*/  put_clnt_odstate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_unhashed_deleg(struct nfs4_delegation *dp)
{
	put_clnt_odstate(dp->dl_clnt_odstate);
	nfs4_unlock_deleg_lease(dp);
	nfs4_put_stid(&dp->dl_stid);
}