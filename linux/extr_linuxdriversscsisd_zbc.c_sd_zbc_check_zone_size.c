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
typedef  unsigned char u8 ;
typedef  scalar_t__ u64 ;
struct scsi_disk {scalar_t__ capacity; scalar_t__ first_scan; int /*<<< orphan*/  device; } ;
typedef  scalar_t__ sector_t ;
typedef  int s64 ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  SD_ZBC_BUF_SIZE ; 
 scalar_t__ UINT_MAX ; 
 int get_unaligned_be32 (unsigned char*) ; 
 scalar_t__ get_unaligned_be64 (unsigned char*) ; 
 int /*<<< orphan*/  is_power_of_2 (scalar_t__) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ logical_to_sectors (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*) ; 
 int sd_zbc_report_zones (struct scsi_disk*,unsigned char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static s64 sd_zbc_check_zone_size(struct scsi_disk *sdkp)
{
	u64 zone_blocks = 0;
	sector_t block = 0;
	unsigned char *buf;
	unsigned char *rec;
	unsigned int buf_len;
	unsigned int list_length;
	s64 ret;
	u8 same;

	/* Get a buffer */
	buf = kmalloc(SD_ZBC_BUF_SIZE, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	/* Do a report zone to get the same field */
	ret = sd_zbc_report_zones(sdkp, buf, SD_ZBC_BUF_SIZE, 0);
	if (ret)
		goto out_free;

	same = buf[4] & 0x0f;
	if (same > 0) {
		rec = &buf[64];
		zone_blocks = get_unaligned_be64(&rec[8]);
		goto out;
	}

	/*
	 * Check the size of all zones: all zones must be of
	 * equal size, except the last zone which can be smaller
	 * than other zones.
	 */
	do {

		/* Parse REPORT ZONES header */
		list_length = get_unaligned_be32(&buf[0]) + 64;
		rec = buf + 64;
		buf_len = min(list_length, SD_ZBC_BUF_SIZE);

		/* Parse zone descriptors */
		while (rec < buf + buf_len) {
			u64 this_zone_blocks = get_unaligned_be64(&rec[8]);

			if (zone_blocks == 0) {
				zone_blocks = this_zone_blocks;
			} else if (this_zone_blocks != zone_blocks &&
				   (block + this_zone_blocks < sdkp->capacity
				    || this_zone_blocks > zone_blocks)) {
				zone_blocks = 0;
				goto out;
			}
			block += this_zone_blocks;
			rec += 64;
		}

		if (block < sdkp->capacity) {
			ret = sd_zbc_report_zones(sdkp, buf,
						  SD_ZBC_BUF_SIZE, block);
			if (ret)
				goto out_free;
		}

	} while (block < sdkp->capacity);

out:
	if (!zone_blocks) {
		if (sdkp->first_scan)
			sd_printk(KERN_NOTICE, sdkp,
				  "Devices with non constant zone "
				  "size are not supported\n");
		ret = -ENODEV;
	} else if (!is_power_of_2(zone_blocks)) {
		if (sdkp->first_scan)
			sd_printk(KERN_NOTICE, sdkp,
				  "Devices with non power of 2 zone "
				  "size are not supported\n");
		ret = -ENODEV;
	} else if (logical_to_sectors(sdkp->device, zone_blocks) > UINT_MAX) {
		if (sdkp->first_scan)
			sd_printk(KERN_NOTICE, sdkp,
				  "Zone size too large\n");
		ret = -ENODEV;
	} else {
		ret = zone_blocks;
	}

out_free:
	kfree(buf);

	return ret;
}