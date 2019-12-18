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
struct nfsd_net {int /*<<< orphan*/  clientid_counter; int /*<<< orphan*/  boot_time; } ;
struct TYPE_2__ {scalar_t__ cl_id; int /*<<< orphan*/  cl_boot; } ;
struct nfs4_client {TYPE_1__ cl_clientid; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_confirm (struct nfs4_client*,struct nfsd_net*) ; 

__attribute__((used)) static void gen_clid(struct nfs4_client *clp, struct nfsd_net *nn)
{
	clp->cl_clientid.cl_boot = nn->boot_time;
	clp->cl_clientid.cl_id = nn->clientid_counter++;
	gen_confirm(clp, nn);
}