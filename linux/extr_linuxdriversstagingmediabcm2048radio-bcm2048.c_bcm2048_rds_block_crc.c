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
struct TYPE_2__ {int* radio_text; } ;
struct bcm2048_device {TYPE_1__ rds_info; } ;

/* Variables and functions */
 int BCM2048_RDS_CRC_MASK ; 

__attribute__((used)) static int bcm2048_rds_block_crc(struct bcm2048_device *bdev, int i)
{
	return bdev->rds_info.radio_text[i] & BCM2048_RDS_CRC_MASK;
}