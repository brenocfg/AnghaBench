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
typedef  int u32 ;
struct scsi_disk {scalar_t__ capacity; scalar_t__ first_scan; int /*<<< orphan*/  urswrz; } ;
typedef  int int64_t ;

/* Variables and functions */
 int EFBIG ; 
 int ENODEV ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  sd_is_zoned (struct scsi_disk*) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*) ; 
 int sd_zbc_check_capacity (struct scsi_disk*,unsigned char*) ; 
 int sd_zbc_check_zone_size (struct scsi_disk*) ; 
 int /*<<< orphan*/  sd_zbc_cleanup (struct scsi_disk*) ; 
 int sd_zbc_read_zoned_characteristics (struct scsi_disk*,unsigned char*) ; 
 int sd_zbc_setup (struct scsi_disk*,int) ; 

int sd_zbc_read_zones(struct scsi_disk *sdkp, unsigned char *buf)
{
	int64_t zone_blocks;
	int ret;

	if (!sd_is_zoned(sdkp))
		/*
		 * Device managed or normal SCSI disk,
		 * no special handling required
		 */
		return 0;

	/* Get zoned block device characteristics */
	ret = sd_zbc_read_zoned_characteristics(sdkp, buf);
	if (ret)
		goto err;

	/*
	 * Check for unconstrained reads: host-managed devices with
	 * constrained reads (drives failing read after write pointer)
	 * are not supported.
	 */
	if (!sdkp->urswrz) {
		if (sdkp->first_scan)
			sd_printk(KERN_NOTICE, sdkp,
			  "constrained reads devices are not supported\n");
		ret = -ENODEV;
		goto err;
	}

	/* Check capacity */
	ret = sd_zbc_check_capacity(sdkp, buf);
	if (ret)
		goto err;

	/*
	 * Check zone size: only devices with a constant zone size (except
	 * an eventual last runt zone) that is a power of 2 are supported.
	 */
	zone_blocks = sd_zbc_check_zone_size(sdkp);
	ret = -EFBIG;
	if (zone_blocks != (u32)zone_blocks)
		goto err;
	ret = zone_blocks;
	if (ret < 0)
		goto err;

	/* The drive satisfies the kernel restrictions: set it up */
	ret = sd_zbc_setup(sdkp, zone_blocks);
	if (ret)
		goto err;

	return 0;

err:
	sdkp->capacity = 0;
	sd_zbc_cleanup(sdkp);

	return ret;
}