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
struct TYPE_2__ {int* radio_text; int rds_pi; } ;
struct bcm2048_device {int fifo_size; TYPE_1__ rds_info; } ;

/* Variables and functions */
 int BCM2048_MAX_RDS_PS ; 
 int BCM2048_RDS_BLOCK_A ; 
 int BCM2048_RDS_BLOCK_MASK ; 
 int BCM2048_RDS_CRC_UNRECOVARABLE ; 
 scalar_t__ BCM2048_RDS_FIFO_DUPLE_SIZE ; 
 int bcm2048_parse_ps_match_b (struct bcm2048_device*,int) ; 
 scalar_t__ bcm2048_parse_ps_match_c (struct bcm2048_device*,int,int) ; 
 int /*<<< orphan*/  bcm2048_parse_ps_match_d (struct bcm2048_device*,int,int) ; 
 int bcm2048_rds_block_crc (struct bcm2048_device*,int) ; 

__attribute__((used)) static void bcm2048_parse_rds_ps(struct bcm2048_device *bdev)
{
	int i, index = 0, crc, match_b = 0, match_c = 0, match_d = 0;

	for (i = 0; i < bdev->fifo_size; i += BCM2048_RDS_FIFO_DUPLE_SIZE) {
		if (match_b) {
			match_b = 0;
			index = bcm2048_parse_ps_match_b(bdev, i);
			if (index >= 0 && index < (BCM2048_MAX_RDS_PS - 1))
				match_c = 1;
			continue;
		} else if (match_c) {
			match_c = 0;
			if (bcm2048_parse_ps_match_c(bdev, i, index))
				match_d = 1;
			continue;
		} else if (match_d) {
			match_d = 0;
			bcm2048_parse_ps_match_d(bdev, i, index);
			continue;
		}

		/* Skip erroneous blocks due to messed up A block altogether */
		if ((bdev->rds_info.radio_text[i] & BCM2048_RDS_BLOCK_MASK) ==
		    BCM2048_RDS_BLOCK_A) {
			crc = bcm2048_rds_block_crc(bdev, i);
			if (crc == BCM2048_RDS_CRC_UNRECOVARABLE)
				continue;
			/* Synchronize to a good RDS PI */
			if (((bdev->rds_info.radio_text[i + 1] << 8) +
			    bdev->rds_info.radio_text[i + 2]) ==
			    bdev->rds_info.rds_pi)
				match_b = 1;
		}
	}
}