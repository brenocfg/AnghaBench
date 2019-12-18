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
struct nfs_client {TYPE_1__* cl_rpcclient; int /*<<< orphan*/ * cl_principal; } ;
struct TYPE_2__ {int /*<<< orphan*/ * cl_principal; } ;

/* Variables and functions */

__attribute__((used)) static void nfs4_root_machine_cred(struct nfs_client *clp)
{

	/* Force root creds instead of machine */
	clp->cl_principal = NULL;
	clp->cl_rpcclient->cl_principal = NULL;
}