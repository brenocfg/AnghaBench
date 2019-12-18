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
struct TYPE_2__ {int /*<<< orphan*/  designator; int /*<<< orphan*/  designator_len; } ;
struct pnfs_block_volume {TYPE_1__ scsi; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct block_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct block_device*) ; 
 int /*<<< orphan*/  PTR_ERR (struct block_device*) ; 
 struct block_device* blkdev_get_by_path (char const*,int,int /*<<< orphan*/ *) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct block_device *
bl_open_udev_path(struct pnfs_block_volume *v)
{
	struct block_device *bdev;
	const char *devname;

	devname = kasprintf(GFP_KERNEL, "/dev/disk/by-id/wwn-0x%*phN",
				v->scsi.designator_len, v->scsi.designator);
	if (!devname)
		return ERR_PTR(-ENOMEM);

	bdev = blkdev_get_by_path(devname, FMODE_READ | FMODE_WRITE, NULL);
	if (IS_ERR(bdev)) {
		pr_warn("pNFS: failed to open device %s (%ld)\n",
			devname, PTR_ERR(bdev));
	}

	kfree(devname);
	return bdev;
}