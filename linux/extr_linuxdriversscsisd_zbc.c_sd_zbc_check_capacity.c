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
struct scsi_disk {scalar_t__ rc_basis; scalar_t__ capacity; scalar_t__ first_scan; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  SD_BUF_SIZE ; 
 scalar_t__ get_unaligned_be64 (unsigned char*) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*,unsigned long long,unsigned long long) ; 
 int sd_zbc_report_zones (struct scsi_disk*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_zbc_check_capacity(struct scsi_disk *sdkp, unsigned char *buf)
{
	sector_t lba;
	int ret;

	if (sdkp->rc_basis != 0)
		return 0;

	/* Do a report zone to get the maximum LBA to check capacity */
	ret = sd_zbc_report_zones(sdkp, buf, SD_BUF_SIZE, 0);
	if (ret)
		return ret;

	/* The max_lba field is the capacity of this device */
	lba = get_unaligned_be64(&buf[8]);
	if (lba + 1 == sdkp->capacity)
		return 0;

	if (sdkp->first_scan)
		sd_printk(KERN_WARNING, sdkp,
			  "Changing capacity from %llu to max LBA+1 %llu\n",
			  (unsigned long long)sdkp->capacity,
			  (unsigned long long)lba + 1);
	sdkp->capacity = lba + 1;

	return 0;
}