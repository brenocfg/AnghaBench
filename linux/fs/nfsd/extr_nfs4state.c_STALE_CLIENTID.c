#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct nfsd_net {scalar_t__ boot_time; } ;
struct TYPE_3__ {scalar_t__ cl_boot; int /*<<< orphan*/  cl_id; } ;
typedef  TYPE_1__ clientid_t ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
STALE_CLIENTID(clientid_t *clid, struct nfsd_net *nn)
{
	/*
	 * We're assuming the clid was not given out from a boot
	 * precisely 2^32 (about 136 years) before this one.  That seems
	 * a safe assumption:
	 */
	if (clid->cl_boot == (u32)nn->boot_time)
		return 0;
	dprintk("NFSD stale clientid (%08x/%08x) boot_time %08lx\n",
		clid->cl_boot, clid->cl_id, nn->boot_time);
	return 1;
}