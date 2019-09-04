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
struct TYPE_2__ {int* radio_text; int rds_rt_group_b; int rds_rt_ab; int /*<<< orphan*/  rds_rt; } ;
struct bcm2048_device {TYPE_1__ rds_info; } ;

/* Variables and functions */
 int BCM2048_RDS_BLOCK_B ; 
 int BCM2048_RDS_BLOCK_MASK ; 
 int BCM2048_RDS_CRC_UNRECOVARABLE ; 
 int BCM2048_RDS_GROUP_AB_MASK ; 
 int BCM2048_RDS_RT ; 
 int BCM2048_RDS_RT_AB_MASK ; 
 int BCM2048_RDS_RT_INDEX ; 
 int EIO ; 
 int bcm2048_rds_block_crc (struct bcm2048_device*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm2048_parse_rt_match_b(struct bcm2048_device *bdev, int i)
{
	int crc, rt_id, rt_group_b, rt_ab, index = 0;

	crc = bcm2048_rds_block_crc(bdev, i);

	if (crc == BCM2048_RDS_CRC_UNRECOVARABLE)
		return -EIO;

	if ((bdev->rds_info.radio_text[i] & BCM2048_RDS_BLOCK_MASK) ==
	    BCM2048_RDS_BLOCK_B) {
		rt_id = bdev->rds_info.radio_text[i + 1] &
			BCM2048_RDS_BLOCK_MASK;
		rt_group_b = bdev->rds_info.radio_text[i + 1] &
			BCM2048_RDS_GROUP_AB_MASK;
		rt_ab = bdev->rds_info.radio_text[i + 2] &
				BCM2048_RDS_RT_AB_MASK;

		if (rt_group_b != bdev->rds_info.rds_rt_group_b) {
			memset(bdev->rds_info.rds_rt, 0,
			       sizeof(bdev->rds_info.rds_rt));
			bdev->rds_info.rds_rt_group_b = rt_group_b;
		}

		if (rt_id == BCM2048_RDS_RT) {
			/* A to B or (vice versa), means: clear screen */
			if (rt_ab != bdev->rds_info.rds_rt_ab) {
				memset(bdev->rds_info.rds_rt, 0,
				       sizeof(bdev->rds_info.rds_rt));
				bdev->rds_info.rds_rt_ab = rt_ab;
			}

			index = bdev->rds_info.radio_text[i + 2] &
					BCM2048_RDS_RT_INDEX;

			if (bdev->rds_info.rds_rt_group_b)
				index <<= 1;
			else
				index <<= 2;

			return index;
		}
	}

	return -EIO;
}