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
struct TYPE_2__ {scalar_t__* radio_text; scalar_t__* rds_ps; } ;
struct bcm2048_device {TYPE_1__ rds_info; } ;

/* Variables and functions */

__attribute__((used)) static void bcm2048_parse_rds_ps_block(struct bcm2048_device *bdev, int i,
				       int index, int crc)
{
	/* Good data will overwrite poor data */
	if (crc) {
		if (!bdev->rds_info.rds_ps[index])
			bdev->rds_info.rds_ps[index] =
				bdev->rds_info.radio_text[i + 1];
		if (!bdev->rds_info.rds_ps[index + 1])
			bdev->rds_info.rds_ps[index + 1] =
				bdev->rds_info.radio_text[i + 2];
	} else {
		bdev->rds_info.rds_ps[index] =
			bdev->rds_info.radio_text[i + 1];
		bdev->rds_info.rds_ps[index + 1] =
			bdev->rds_info.radio_text[i + 2];
	}
}