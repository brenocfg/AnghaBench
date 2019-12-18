#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  wr_verifier; int /*<<< orphan*/  wr_stable_how; } ;
struct nfsd4_copy {int cp_synchronous; TYPE_2__* cp_clp; TYPE_1__ cp_res; } ;
struct TYPE_4__ {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_UNSTABLE ; 
 int /*<<< orphan*/  gen_boot_verifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfsd4_init_copy_res(struct nfsd4_copy *copy, bool sync)
{
	copy->cp_res.wr_stable_how = NFS_UNSTABLE;
	copy->cp_synchronous = sync;
	gen_boot_verifier(&copy->cp_res.wr_verifier, copy->cp_clp->net);
}