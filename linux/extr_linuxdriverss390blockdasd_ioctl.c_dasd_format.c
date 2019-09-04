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
struct format_data_t {int /*<<< orphan*/  blksize; int /*<<< orphan*/  start_unit; int /*<<< orphan*/  intensity; int /*<<< orphan*/  stop_unit; } ;
struct dasd_device {scalar_t__ state; TYPE_3__* discipline; TYPE_1__* cdev; } ;
struct dasd_block {int /*<<< orphan*/  gdp; struct dasd_device* base; } ;
struct block_device {TYPE_2__* bd_inode; } ;
struct TYPE_6__ {int (* format_device ) (struct dasd_device*,struct format_data_t*,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  i_blkbits; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DASD_STATE_BASIC ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBF_NOTICE ; 
 int EAGAIN ; 
 int EBUSY ; 
 int EPERM ; 
 struct block_device* bdget_disk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdput (struct block_device*) ; 
 int /*<<< orphan*/  blksize_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct dasd_device*,struct format_data_t*,int) ; 
 int stub2 (struct dasd_device*,struct format_data_t*,int) ; 

__attribute__((used)) static int
dasd_format(struct dasd_block *block, struct format_data_t *fdata)
{
	struct dasd_device *base;
	int rc;

	base = block->base;
	if (base->discipline->format_device == NULL)
		return -EPERM;

	if (base->state != DASD_STATE_BASIC) {
		pr_warn("%s: The DASD cannot be formatted while it is enabled\n",
			dev_name(&base->cdev->dev));
		return -EBUSY;
	}

	DBF_DEV_EVENT(DBF_NOTICE, base,
		      "formatting units %u to %u (%u B blocks) flags %u",
		      fdata->start_unit,
		      fdata->stop_unit, fdata->blksize, fdata->intensity);

	/* Since dasdfmt keeps the device open after it was disabled,
	 * there still exists an inode for this device.
	 * We must update i_blkbits, otherwise we might get errors when
	 * enabling the device later.
	 */
	if (fdata->start_unit == 0) {
		struct block_device *bdev = bdget_disk(block->gdp, 0);
		bdev->bd_inode->i_blkbits = blksize_bits(fdata->blksize);
		bdput(bdev);
	}

	rc = base->discipline->format_device(base, fdata, 1);
	if (rc == -EAGAIN)
		rc = base->discipline->format_device(base, fdata, 0);

	return rc;
}