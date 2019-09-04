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
struct pnfs_layout_segment {TYPE_1__* pls_layout; } ;
struct nfs4_deviceid_node {int /*<<< orphan*/  deviceid; int /*<<< orphan*/  nfs_client; int /*<<< orphan*/  ld; } ;
struct TYPE_2__ {int /*<<< orphan*/  plh_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ff_layout_has_available_ds (struct pnfs_layout_segment*) ; 
 int /*<<< orphan*/  nfs4_delete_deviceid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnfs_error_mark_layout_for_return (int /*<<< orphan*/ ,struct pnfs_layout_segment*) ; 

__attribute__((used)) static void ff_layout_mark_devid_invalid(struct pnfs_layout_segment *lseg,
		struct nfs4_deviceid_node *devid)
{
	nfs4_delete_deviceid(devid->ld, devid->nfs_client, &devid->deviceid);
	if (!ff_layout_has_available_ds(lseg))
		pnfs_error_mark_layout_for_return(lseg->pls_layout->plh_inode,
				lseg);
}