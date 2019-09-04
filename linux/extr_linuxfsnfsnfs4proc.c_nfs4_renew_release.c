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
struct nfs_client {int /*<<< orphan*/  cl_count; } ;
struct nfs4_renewdata {struct nfs_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfs4_renewdata*) ; 
 int /*<<< orphan*/  nfs4_schedule_state_renewal (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs_put_client (struct nfs_client*) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs4_renew_release(void *calldata)
{
	struct nfs4_renewdata *data = calldata;
	struct nfs_client *clp = data->client;

	if (refcount_read(&clp->cl_count) > 1)
		nfs4_schedule_state_renewal(clp);
	nfs_put_client(clp);
	kfree(data);
}