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
struct nfs4_flexfile_layout {int /*<<< orphan*/  generic_hdr; } ;
struct nfs42_layoutstat_args {int /*<<< orphan*/ * devinfo; int /*<<< orphan*/  num_dev; TYPE_2__* inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  layout; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 struct nfs4_flexfile_layout* FF_LAYOUT_FROM_HDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 TYPE_1__* NFS_I (TYPE_2__*) ; 
 int PNFS_LAYOUTSTATS_MAXDEV ; 
 int /*<<< orphan*/  ff_layout_mirror_prepare_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc_array (int const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ff_layout_prepare_layoutstats(struct nfs42_layoutstat_args *args)
{
	struct nfs4_flexfile_layout *ff_layout;
	const int dev_count = PNFS_LAYOUTSTATS_MAXDEV;

	/* For now, send at most PNFS_LAYOUTSTATS_MAXDEV statistics */
	args->devinfo = kmalloc_array(dev_count, sizeof(*args->devinfo), GFP_NOIO);
	if (!args->devinfo)
		return -ENOMEM;

	spin_lock(&args->inode->i_lock);
	ff_layout = FF_LAYOUT_FROM_HDR(NFS_I(args->inode)->layout);
	args->num_dev = ff_layout_mirror_prepare_stats(&ff_layout->generic_hdr,
			&args->devinfo[0], dev_count);
	spin_unlock(&args->inode->i_lock);
	if (!args->num_dev) {
		kfree(args->devinfo);
		args->devinfo = NULL;
		return -ENOENT;
	}

	return 0;
}