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
struct nfs4_client {int /*<<< orphan*/  async_copies; int /*<<< orphan*/  cl_sessions; int /*<<< orphan*/  cl_delegations; int /*<<< orphan*/  cl_lo_states; } ;

/* Variables and functions */
 scalar_t__ client_has_openowners (struct nfs4_client*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool client_has_state(struct nfs4_client *clp)
{
	return client_has_openowners(clp)
#ifdef CONFIG_NFSD_PNFS
		|| !list_empty(&clp->cl_lo_states)
#endif
		|| !list_empty(&clp->cl_delegations)
		|| !list_empty(&clp->cl_sessions)
		|| !list_empty(&clp->async_copies);
}