#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct t10_pi_tuple {int dummy; } ;
struct scsi_disk {scalar_t__ protection_type; int /*<<< orphan*/  ATO; struct scsi_device* device; struct gendisk* disk; } ;
struct scsi_device {int /*<<< orphan*/  host; } ;
struct gendisk {int dummy; } ;
struct blk_integrity {int tuple_size; int tag_size; int /*<<< orphan*/  flags; TYPE_1__* profile; } ;
typedef  int /*<<< orphan*/  bi ;
struct TYPE_5__ {int name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_INTEGRITY_DEVICE_CAPABLE ; 
 int /*<<< orphan*/  BLK_INTEGRITY_IP_CHECKSUM ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int SHOST_DIX_GUARD_IP ; 
 scalar_t__ T10_PI_TYPE3_PROTECTION ; 
 int /*<<< orphan*/  blk_integrity_register (struct gendisk*,struct blk_integrity*) ; 
 int /*<<< orphan*/  memset (struct blk_integrity*,int /*<<< orphan*/ ,int) ; 
 int scsi_host_dif_capable (int /*<<< orphan*/ ,scalar_t__) ; 
 int scsi_host_dix_capable (int /*<<< orphan*/ ,scalar_t__) ; 
 int scsi_host_get_guard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*,int) ; 
 TYPE_1__ t10_pi_type1_crc ; 
 TYPE_1__ t10_pi_type1_ip ; 
 TYPE_1__ t10_pi_type3_crc ; 
 TYPE_1__ t10_pi_type3_ip ; 

void sd_dif_config_host(struct scsi_disk *sdkp)
{
	struct scsi_device *sdp = sdkp->device;
	struct gendisk *disk = sdkp->disk;
	u8 type = sdkp->protection_type;
	struct blk_integrity bi;
	int dif, dix;

	dif = scsi_host_dif_capable(sdp->host, type);
	dix = scsi_host_dix_capable(sdp->host, type);

	if (!dix && scsi_host_dix_capable(sdp->host, 0)) {
		dif = 0; dix = 1;
	}

	if (!dix)
		return;

	memset(&bi, 0, sizeof(bi));

	/* Enable DMA of protection information */
	if (scsi_host_get_guard(sdkp->device->host) & SHOST_DIX_GUARD_IP) {
		if (type == T10_PI_TYPE3_PROTECTION)
			bi.profile = &t10_pi_type3_ip;
		else
			bi.profile = &t10_pi_type1_ip;

		bi.flags |= BLK_INTEGRITY_IP_CHECKSUM;
	} else
		if (type == T10_PI_TYPE3_PROTECTION)
			bi.profile = &t10_pi_type3_crc;
		else
			bi.profile = &t10_pi_type1_crc;

	bi.tuple_size = sizeof(struct t10_pi_tuple);
	sd_printk(KERN_NOTICE, sdkp,
		  "Enabling DIX %s protection\n", bi.profile->name);

	if (dif && type) {
		bi.flags |= BLK_INTEGRITY_DEVICE_CAPABLE;

		if (!sdkp->ATO)
			goto out;

		if (type == T10_PI_TYPE3_PROTECTION)
			bi.tag_size = sizeof(u16) + sizeof(u32);
		else
			bi.tag_size = sizeof(u16);

		sd_printk(KERN_NOTICE, sdkp, "DIF application tag size %u\n",
			  bi.tag_size);
	}

out:
	blk_integrity_register(disk, &bi);
}