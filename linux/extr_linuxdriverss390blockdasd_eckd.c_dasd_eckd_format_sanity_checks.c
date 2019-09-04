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
struct format_data_t {int start_unit; int stop_unit; int blksize; } ;
struct TYPE_3__ {int trk_per_cyl; } ;
struct dasd_eckd_private {int real_cyl; TYPE_1__ rdc_data; } ;
struct dasd_device {TYPE_2__* cdev; struct dasd_eckd_private* private; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ dasd_check_blocksize (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int dasd_eckd_format_sanity_checks(struct dasd_device *base,
					  struct format_data_t *fdata)
{
	struct dasd_eckd_private *private = base->private;

	if (fdata->start_unit >=
	    (private->real_cyl * private->rdc_data.trk_per_cyl)) {
		dev_warn(&base->cdev->dev,
			 "Start track number %u used in formatting is too big\n",
			 fdata->start_unit);
		return -EINVAL;
	}
	if (fdata->stop_unit >=
	    (private->real_cyl * private->rdc_data.trk_per_cyl)) {
		dev_warn(&base->cdev->dev,
			 "Stop track number %u used in formatting is too big\n",
			 fdata->stop_unit);
		return -EINVAL;
	}
	if (fdata->start_unit > fdata->stop_unit) {
		dev_warn(&base->cdev->dev,
			 "Start track %u used in formatting exceeds end track\n",
			 fdata->start_unit);
		return -EINVAL;
	}
	if (dasd_check_blocksize(fdata->blksize) != 0) {
		dev_warn(&base->cdev->dev,
			 "The DASD cannot be formatted with block size %u\n",
			 fdata->blksize);
		return -EINVAL;
	}
	return 0;
}