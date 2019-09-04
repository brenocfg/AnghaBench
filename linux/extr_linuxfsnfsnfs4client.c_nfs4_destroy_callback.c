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
struct nfs_client {int /*<<< orphan*/  cl_net; TYPE_1__* cl_mvops; int /*<<< orphan*/  cl_res_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  minor_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_CS_CALLBACK ; 
 scalar_t__ __test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_callback_down (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs4_destroy_callback(struct nfs_client *clp)
{
	if (__test_and_clear_bit(NFS_CS_CALLBACK, &clp->cl_res_state))
		nfs_callback_down(clp->cl_mvops->minor_version, clp->cl_net);
}