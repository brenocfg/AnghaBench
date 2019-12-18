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
struct TYPE_2__ {int /*<<< orphan*/  designator; int /*<<< orphan*/  designator_len; int /*<<< orphan*/  designator_type; } ;
struct pnfs_block_volume {TYPE_1__ scsi; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct block_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct block_device* blkdev_get_by_path (char const*,int,int /*<<< orphan*/ *) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char const*) ; 

__attribute__((used)) static struct block_device *
bl_open_dm_mpath_udev_path(struct pnfs_block_volume *v)
{
	struct block_device *bdev;
	const char *devname;

	devname = kasprintf(GFP_KERNEL,
			"/dev/disk/by-id/dm-uuid-mpath-%d%*phN",
			v->scsi.designator_type,
			v->scsi.designator_len, v->scsi.designator);
	if (!devname)
		return ERR_PTR(-ENOMEM);

	bdev = blkdev_get_by_path(devname, FMODE_READ | FMODE_WRITE, NULL);
	kfree(devname);
	return bdev;
}