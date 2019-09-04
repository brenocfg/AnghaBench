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
typedef  void* u16 ;
struct TYPE_2__ {int* radio_text; void* rds_pi; } ;
struct bcm2048_device {int fifo_size; TYPE_1__ rds_info; } ;

/* Variables and functions */
 int BCM2048_RDS_BLOCK_A ; 
 scalar_t__ BCM2048_RDS_FIFO_DUPLE_SIZE ; 

__attribute__((used)) static void bcm2048_parse_rds_pi(struct bcm2048_device *bdev)
{
	int i, cnt = 0;
	u16 pi;

	for (i = 0; i < bdev->fifo_size; i += BCM2048_RDS_FIFO_DUPLE_SIZE) {
		/* Block A match, only data without crc errors taken */
		if (bdev->rds_info.radio_text[i] == BCM2048_RDS_BLOCK_A) {
			pi = (bdev->rds_info.radio_text[i + 1] << 8) +
				bdev->rds_info.radio_text[i + 2];

			if (!bdev->rds_info.rds_pi) {
				bdev->rds_info.rds_pi = pi;
				return;
			}
			if (pi != bdev->rds_info.rds_pi) {
				cnt++;
				if (cnt > 3) {
					bdev->rds_info.rds_pi = pi;
					cnt = 0;
				}
			} else {
				cnt = 0;
			}
		}
	}
}