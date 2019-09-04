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
struct scsi_sense_hdr {int dummy; } ;
struct scsi_mode_data {unsigned int length; int header_length; int block_descriptor_length; } ;
struct TYPE_2__ {int speed; int mask; int capacity; } ;
struct scsi_cd {int readcd_known; unsigned char readcd_cdda; int writeable; TYPE_1__ cdi; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int CDC_CD_R ; 
 int CDC_CD_RW ; 
 int CDC_CLOSE_TRAY ; 
 int CDC_DVD ; 
 int CDC_DVD_R ; 
 int CDC_DVD_RAM ; 
 int CDC_MRW ; 
 int CDC_MRW_W ; 
 int CDC_OPEN_TRAY ; 
 int CDC_RAM ; 
 int CDC_SELECT_DISC ; 
 int CDC_SELECT_SPEED ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  MAX_RETRIES ; 
 int /*<<< orphan*/  SR_TIMEOUT ; 
 int cdrom_number_of_slots (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int) ; 
 unsigned char mechtype_cartridge_changer ; 
 unsigned char mechtype_individual_changer ; 
 int scsi_mode_sense (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char*,unsigned int,int /*<<< orphan*/ ,int,struct scsi_mode_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_status_is_good (int) ; 
 int /*<<< orphan*/  scsi_test_unit_ready (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  sr_printk (int /*<<< orphan*/ ,struct scsi_cd*,char*,...) ; 

__attribute__((used)) static void get_capabilities(struct scsi_cd *cd)
{
	unsigned char *buffer;
	struct scsi_mode_data data;
	struct scsi_sense_hdr sshdr;
	unsigned int ms_len = 128;
	int rc, n;

	static const char *loadmech[] =
	{
		"caddy",
		"tray",
		"pop-up",
		"",
		"changer",
		"cartridge changer",
		"",
		""
	};


	/* allocate transfer buffer */
	buffer = kmalloc(512, GFP_KERNEL | GFP_DMA);
	if (!buffer) {
		sr_printk(KERN_ERR, cd, "out of memory.\n");
		return;
	}

	/* eat unit attentions */
	scsi_test_unit_ready(cd->device, SR_TIMEOUT, MAX_RETRIES, &sshdr);

	/* ask for mode page 0x2a */
	rc = scsi_mode_sense(cd->device, 0, 0x2a, buffer, ms_len,
			     SR_TIMEOUT, 3, &data, NULL);

	if (!scsi_status_is_good(rc) || data.length > ms_len ||
	    data.header_length + data.block_descriptor_length > data.length) {
		/* failed, drive doesn't have capabilities mode page */
		cd->cdi.speed = 1;
		cd->cdi.mask |= (CDC_CD_R | CDC_CD_RW | CDC_DVD_R |
				 CDC_DVD | CDC_DVD_RAM |
				 CDC_SELECT_DISC | CDC_SELECT_SPEED |
				 CDC_MRW | CDC_MRW_W | CDC_RAM);
		kfree(buffer);
		sr_printk(KERN_INFO, cd, "scsi-1 drive");
		return;
	}

	n = data.header_length + data.block_descriptor_length;
	cd->cdi.speed = ((buffer[n + 8] << 8) + buffer[n + 9]) / 176;
	cd->readcd_known = 1;
	cd->readcd_cdda = buffer[n + 5] & 0x01;
	/* print some capability bits */
	sr_printk(KERN_INFO, cd,
		  "scsi3-mmc drive: %dx/%dx %s%s%s%s%s%s\n",
		  ((buffer[n + 14] << 8) + buffer[n + 15]) / 176,
		  cd->cdi.speed,
		  buffer[n + 3] & 0x01 ? "writer " : "", /* CD Writer */
		  buffer[n + 3] & 0x20 ? "dvd-ram " : "",
		  buffer[n + 2] & 0x02 ? "cd/rw " : "", /* can read rewriteable */
		  buffer[n + 4] & 0x20 ? "xa/form2 " : "",	/* can read xa/from2 */
		  buffer[n + 5] & 0x01 ? "cdda " : "", /* can read audio data */
		  loadmech[buffer[n + 6] >> 5]);
	if ((buffer[n + 6] >> 5) == 0)
		/* caddy drives can't close tray... */
		cd->cdi.mask |= CDC_CLOSE_TRAY;
	if ((buffer[n + 2] & 0x8) == 0)
		/* not a DVD drive */
		cd->cdi.mask |= CDC_DVD;
	if ((buffer[n + 3] & 0x20) == 0)
		/* can't write DVD-RAM media */
		cd->cdi.mask |= CDC_DVD_RAM;
	if ((buffer[n + 3] & 0x10) == 0)
		/* can't write DVD-R media */
		cd->cdi.mask |= CDC_DVD_R;
	if ((buffer[n + 3] & 0x2) == 0)
		/* can't write CD-RW media */
		cd->cdi.mask |= CDC_CD_RW;
	if ((buffer[n + 3] & 0x1) == 0)
		/* can't write CD-R media */
		cd->cdi.mask |= CDC_CD_R;
	if ((buffer[n + 6] & 0x8) == 0)
		/* can't eject */
		cd->cdi.mask |= CDC_OPEN_TRAY;

	if ((buffer[n + 6] >> 5) == mechtype_individual_changer ||
	    (buffer[n + 6] >> 5) == mechtype_cartridge_changer)
		cd->cdi.capacity =
		    cdrom_number_of_slots(&cd->cdi);
	if (cd->cdi.capacity <= 1)
		/* not a changer */
		cd->cdi.mask |= CDC_SELECT_DISC;
	/*else    I don't think it can close its tray
		cd->cdi.mask |= CDC_CLOSE_TRAY; */

	/*
	 * if DVD-RAM, MRW-W or CD-RW, we are randomly writable
	 */
	if ((cd->cdi.mask & (CDC_DVD_RAM | CDC_MRW_W | CDC_RAM | CDC_CD_RW)) !=
			(CDC_DVD_RAM | CDC_MRW_W | CDC_RAM | CDC_CD_RW)) {
		cd->writeable = 1;
	}

	kfree(buffer);
}