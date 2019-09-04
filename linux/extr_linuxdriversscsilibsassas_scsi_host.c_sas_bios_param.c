#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct scsi_device {int dummy; } ;
struct block_device {int dummy; } ;
typedef  int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  sector_div (int,int) ; 

int sas_bios_param(struct scsi_device *scsi_dev,
			  struct block_device *bdev,
			  sector_t capacity, int *hsc)
{
	hsc[0] = 255;
	hsc[1] = 63;
	sector_div(capacity, 255*63);
	hsc[2] = capacity;

	return 0;
}