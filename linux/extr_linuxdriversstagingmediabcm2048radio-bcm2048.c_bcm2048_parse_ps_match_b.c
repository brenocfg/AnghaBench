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
struct TYPE_4__ {int* radio_text; int rds_ps_group; int rds_ps_group_cnt; } ;
struct bcm2048_device {TYPE_2__ rds_info; TYPE_1__* client; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BCM2048_RDS_BLOCK_B ; 
 int BCM2048_RDS_BLOCK_MASK ; 
 int BCM2048_RDS_CRC_NONE ; 
 int BCM2048_RDS_CRC_UNRECOVARABLE ; 
 int BCM2048_RDS_GROUP_AB_MASK ; 
 int BCM2048_RDS_PS ; 
 int BCM2048_RDS_PS_INDEX ; 
 int EIO ; 
 int bcm2048_rds_block_crc (struct bcm2048_device*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int bcm2048_parse_ps_match_b(struct bcm2048_device *bdev, int i)
{
	int crc, index, ps_id, ps_group;

	crc = bcm2048_rds_block_crc(bdev, i);

	if (crc == BCM2048_RDS_CRC_UNRECOVARABLE)
		return -EIO;

	/* Block B Radio PS match */
	if ((bdev->rds_info.radio_text[i] & BCM2048_RDS_BLOCK_MASK) ==
	    BCM2048_RDS_BLOCK_B) {
		ps_id = bdev->rds_info.radio_text[i + 1] &
			BCM2048_RDS_BLOCK_MASK;
		ps_group = bdev->rds_info.radio_text[i + 1] &
			BCM2048_RDS_GROUP_AB_MASK;

		/*
		 * Poor RSSI will lead to RDS data corruption
		 * So using 3 (same) sequential values to justify major changes
		 */
		if (ps_group != bdev->rds_info.rds_ps_group) {
			if (crc == BCM2048_RDS_CRC_NONE) {
				bdev->rds_info.rds_ps_group_cnt++;
				if (bdev->rds_info.rds_ps_group_cnt > 2) {
					bdev->rds_info.rds_ps_group = ps_group;
					bdev->rds_info.rds_ps_group_cnt	= 0;
					dev_err(&bdev->client->dev,
						"RDS PS Group change!\n");
				} else {
					return -EIO;
				}
			} else {
				bdev->rds_info.rds_ps_group_cnt = 0;
			}
		}

		if (ps_id == BCM2048_RDS_PS) {
			index = bdev->rds_info.radio_text[i + 2] &
				BCM2048_RDS_PS_INDEX;
			index <<= 1;
			return index;
		}
	}

	return -EIO;
}