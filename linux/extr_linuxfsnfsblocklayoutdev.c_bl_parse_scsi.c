#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pr_ops {int (* pr_register ) (struct block_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  pr_key; } ;
struct pnfs_block_volume {TYPE_1__ scsi; } ;
struct pnfs_block_dev {int pr_registered; struct block_device* bdev; int /*<<< orphan*/  pr_key; int /*<<< orphan*/  map; int /*<<< orphan*/  len; } ;
struct nfs_server {int dummy; } ;
struct block_device {TYPE_3__* bd_disk; int /*<<< orphan*/  bd_inode; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_6__ {int /*<<< orphan*/  disk_name; TYPE_2__* fops; } ;
struct TYPE_5__ {struct pr_ops* pr_ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 scalar_t__ IS_ERR (struct block_device*) ; 
 int PTR_ERR (struct block_device*) ; 
 int /*<<< orphan*/  bl_map_simple ; 
 struct block_device* bl_open_dm_mpath_udev_path (struct pnfs_block_volume*) ; 
 struct block_device* bl_open_udev_path (struct pnfs_block_volume*) ; 
 int /*<<< orphan*/  bl_validate_designator (struct pnfs_block_volume*) ; 
 int /*<<< orphan*/  blkdev_put (struct block_device*,int) ; 
 int /*<<< orphan*/  i_size_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct block_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bl_parse_scsi(struct nfs_server *server, struct pnfs_block_dev *d,
		struct pnfs_block_volume *volumes, int idx, gfp_t gfp_mask)
{
	struct pnfs_block_volume *v = &volumes[idx];
	struct block_device *bdev;
	const struct pr_ops *ops;
	int error;

	if (!bl_validate_designator(v))
		return -EINVAL;

	bdev = bl_open_dm_mpath_udev_path(v);
	if (IS_ERR(bdev))
		bdev = bl_open_udev_path(v);
	if (IS_ERR(bdev))
		return PTR_ERR(bdev);
	d->bdev = bdev;

	d->len = i_size_read(d->bdev->bd_inode);
	d->map = bl_map_simple;
	d->pr_key = v->scsi.pr_key;

	pr_info("pNFS: using block device %s (reservation key 0x%llx)\n",
		d->bdev->bd_disk->disk_name, d->pr_key);

	ops = d->bdev->bd_disk->fops->pr_ops;
	if (!ops) {
		pr_err("pNFS: block device %s does not support reservations.",
				d->bdev->bd_disk->disk_name);
		error = -EINVAL;
		goto out_blkdev_put;
	}

	error = ops->pr_register(d->bdev, 0, d->pr_key, true);
	if (error) {
		pr_err("pNFS: failed to register key for block device %s.",
				d->bdev->bd_disk->disk_name);
		goto out_blkdev_put;
	}

	d->pr_registered = true;
	return 0;

out_blkdev_put:
	blkdev_put(d->bdev, FMODE_READ | FMODE_WRITE);
	return error;
}