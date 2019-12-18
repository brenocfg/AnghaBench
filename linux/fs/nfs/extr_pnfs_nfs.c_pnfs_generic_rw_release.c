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
struct nfs_pgio_header {TYPE_1__* mds_ops; int /*<<< orphan*/  ds_clp; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rpc_release ) (void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_put_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

void pnfs_generic_rw_release(void *data)
{
	struct nfs_pgio_header *hdr = data;

	nfs_put_client(hdr->ds_clp);
	hdr->mds_ops->rpc_release(data);
}