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
struct TYPE_2__ {int /*<<< orphan*/  cl_ref; } ;
struct nfs4_client {TYPE_1__ cl_nfsdfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_client ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drop_client(struct nfs4_client *clp)
{
	kref_put(&clp->cl_nfsdfs.cl_ref, __free_client);
}