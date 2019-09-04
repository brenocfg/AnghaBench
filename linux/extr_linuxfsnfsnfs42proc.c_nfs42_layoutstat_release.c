#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int num_dev; struct nfs42_layoutstat_devinfo* devinfo; int /*<<< orphan*/  inode; } ;
struct TYPE_7__ {TYPE_1__* ops; } ;
struct nfs42_layoutstat_devinfo {TYPE_2__ args; int /*<<< orphan*/  inode; TYPE_3__ ld_private; } ;
struct nfs42_layoutstat_data {TYPE_2__ args; int /*<<< orphan*/  inode; TYPE_3__ ld_private; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  layout; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* free ) (TYPE_3__*) ;} ;

/* Variables and functions */
 TYPE_4__* NFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_INO_LAYOUTSTATS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nfs42_layoutstat_devinfo*) ; 
 int /*<<< orphan*/  nfs_iput_and_deactive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_put_layout_hdr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void
nfs42_layoutstat_release(void *calldata)
{
	struct nfs42_layoutstat_data *data = calldata;
	struct nfs42_layoutstat_devinfo *devinfo = data->args.devinfo;
	int i;

	for (i = 0; i < data->args.num_dev; i++) {
		if (devinfo[i].ld_private.ops && devinfo[i].ld_private.ops->free)
			devinfo[i].ld_private.ops->free(&devinfo[i].ld_private);
	}

	pnfs_put_layout_hdr(NFS_I(data->args.inode)->layout);
	smp_mb__before_atomic();
	clear_bit(NFS_INO_LAYOUTSTATS, &NFS_I(data->args.inode)->flags);
	smp_mb__after_atomic();
	nfs_iput_and_deactive(data->inode);
	kfree(data->args.devinfo);
	kfree(data);
}