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
struct TYPE_4__ {int* radio_text; scalar_t__ rds_rt_group_b; } ;
struct bcm2048_device {TYPE_2__ rds_info; TYPE_1__* client; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BCM2048_MAX_RDS_RT ; 
 int BCM2048_RDS_BLOCK_C ; 
 int BCM2048_RDS_BLOCK_MASK ; 
 int BCM2048_RDS_CRC_UNRECOVARABLE ; 
 int /*<<< orphan*/  bcm2048_parse_rds_rt_block (struct bcm2048_device*,int,int,int) ; 
 int bcm2048_rds_block_crc (struct bcm2048_device*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int bcm2048_parse_rt_match_c(struct bcm2048_device *bdev, int i,
				    int index)
{
	int crc;

	crc = bcm2048_rds_block_crc(bdev, i);

	if (crc == BCM2048_RDS_CRC_UNRECOVARABLE)
		return 0;

	if ((index + 2) >= BCM2048_MAX_RDS_RT) {
		dev_err(&bdev->client->dev,
			"Incorrect index = %d\n", index);
		return 0;
	}

	if ((bdev->rds_info.radio_text[i] & BCM2048_RDS_BLOCK_MASK) ==
		BCM2048_RDS_BLOCK_C) {
		if (bdev->rds_info.rds_rt_group_b)
			return 1;
		bcm2048_parse_rds_rt_block(bdev, i, index, crc);
		return 1;
	}

	return 0;
}