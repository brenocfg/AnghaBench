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
typedef  int u8 ;
struct scsi_sense_hdr {scalar_t__ sense_key; int asc; int ascq; } ;
struct scsi_mode_data {int header_length; int length; int block_descriptor_length; int device_specific; } ;
struct scsi_disk {int WCE; int RCD; int DPOFUA; scalar_t__ first_scan; scalar_t__ write_prot; struct scsi_device* device; scalar_t__ cache_override; } ;
struct scsi_device {scalar_t__ type; scalar_t__ wce_default_on; int /*<<< orphan*/  use_16_for_rw; int /*<<< orphan*/  use_10_for_rw; scalar_t__ broken_fua; scalar_t__ use_192_bytes_for_3f; scalar_t__ skip_ms_page_3f; scalar_t__ skip_ms_page_8; } ;

/* Variables and functions */
 scalar_t__ ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int SD_BUF_SIZE ; 
 scalar_t__ TYPE_RBC ; 
 scalar_t__ scsi_sense_valid (struct scsi_sense_hdr*) ; 
 scalar_t__ scsi_status_is_good (int) ; 
 int sd_do_mode_sense (struct scsi_device*,int,int,unsigned char*,int,struct scsi_mode_data*,struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  sd_first_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*,...) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*,char*,char*,char*) ; 

__attribute__((used)) static void
sd_read_cache_type(struct scsi_disk *sdkp, unsigned char *buffer)
{
	int len = 0, res;
	struct scsi_device *sdp = sdkp->device;

	int dbd;
	int modepage;
	int first_len;
	struct scsi_mode_data data;
	struct scsi_sense_hdr sshdr;
	int old_wce = sdkp->WCE;
	int old_rcd = sdkp->RCD;
	int old_dpofua = sdkp->DPOFUA;


	if (sdkp->cache_override)
		return;

	first_len = 4;
	if (sdp->skip_ms_page_8) {
		if (sdp->type == TYPE_RBC)
			goto defaults;
		else {
			if (sdp->skip_ms_page_3f)
				goto defaults;
			modepage = 0x3F;
			if (sdp->use_192_bytes_for_3f)
				first_len = 192;
			dbd = 0;
		}
	} else if (sdp->type == TYPE_RBC) {
		modepage = 6;
		dbd = 8;
	} else {
		modepage = 8;
		dbd = 0;
	}

	/* cautiously ask */
	res = sd_do_mode_sense(sdp, dbd, modepage, buffer, first_len,
			&data, &sshdr);

	if (!scsi_status_is_good(res))
		goto bad_sense;

	if (!data.header_length) {
		modepage = 6;
		first_len = 0;
		sd_first_printk(KERN_ERR, sdkp,
				"Missing header in MODE_SENSE response\n");
	}

	/* that went OK, now ask for the proper length */
	len = data.length;

	/*
	 * We're only interested in the first three bytes, actually.
	 * But the data cache page is defined for the first 20.
	 */
	if (len < 3)
		goto bad_sense;
	else if (len > SD_BUF_SIZE) {
		sd_first_printk(KERN_NOTICE, sdkp, "Truncating mode parameter "
			  "data from %d to %d bytes\n", len, SD_BUF_SIZE);
		len = SD_BUF_SIZE;
	}
	if (modepage == 0x3F && sdp->use_192_bytes_for_3f)
		len = 192;

	/* Get the data */
	if (len > first_len)
		res = sd_do_mode_sense(sdp, dbd, modepage, buffer, len,
				&data, &sshdr);

	if (scsi_status_is_good(res)) {
		int offset = data.header_length + data.block_descriptor_length;

		while (offset < len) {
			u8 page_code = buffer[offset] & 0x3F;
			u8 spf       = buffer[offset] & 0x40;

			if (page_code == 8 || page_code == 6) {
				/* We're interested only in the first 3 bytes.
				 */
				if (len - offset <= 2) {
					sd_first_printk(KERN_ERR, sdkp,
						"Incomplete mode parameter "
							"data\n");
					goto defaults;
				} else {
					modepage = page_code;
					goto Page_found;
				}
			} else {
				/* Go to the next page */
				if (spf && len - offset > 3)
					offset += 4 + (buffer[offset+2] << 8) +
						buffer[offset+3];
				else if (!spf && len - offset > 1)
					offset += 2 + buffer[offset+1];
				else {
					sd_first_printk(KERN_ERR, sdkp,
							"Incomplete mode "
							"parameter data\n");
					goto defaults;
				}
			}
		}

		sd_first_printk(KERN_ERR, sdkp, "No Caching mode page found\n");
		goto defaults;

	Page_found:
		if (modepage == 8) {
			sdkp->WCE = ((buffer[offset + 2] & 0x04) != 0);
			sdkp->RCD = ((buffer[offset + 2] & 0x01) != 0);
		} else {
			sdkp->WCE = ((buffer[offset + 2] & 0x01) == 0);
			sdkp->RCD = 0;
		}

		sdkp->DPOFUA = (data.device_specific & 0x10) != 0;
		if (sdp->broken_fua) {
			sd_first_printk(KERN_NOTICE, sdkp, "Disabling FUA\n");
			sdkp->DPOFUA = 0;
		} else if (sdkp->DPOFUA && !sdkp->device->use_10_for_rw &&
			   !sdkp->device->use_16_for_rw) {
			sd_first_printk(KERN_NOTICE, sdkp,
				  "Uses READ/WRITE(6), disabling FUA\n");
			sdkp->DPOFUA = 0;
		}

		/* No cache flush allowed for write protected devices */
		if (sdkp->WCE && sdkp->write_prot)
			sdkp->WCE = 0;

		if (sdkp->first_scan || old_wce != sdkp->WCE ||
		    old_rcd != sdkp->RCD || old_dpofua != sdkp->DPOFUA)
			sd_printk(KERN_NOTICE, sdkp,
				  "Write cache: %s, read cache: %s, %s\n",
				  sdkp->WCE ? "enabled" : "disabled",
				  sdkp->RCD ? "disabled" : "enabled",
				  sdkp->DPOFUA ? "supports DPO and FUA"
				  : "doesn't support DPO or FUA");

		return;
	}

bad_sense:
	if (scsi_sense_valid(&sshdr) &&
	    sshdr.sense_key == ILLEGAL_REQUEST &&
	    sshdr.asc == 0x24 && sshdr.ascq == 0x0)
		/* Invalid field in CDB */
		sd_first_printk(KERN_NOTICE, sdkp, "Cache data unavailable\n");
	else
		sd_first_printk(KERN_ERR, sdkp,
				"Asking for cache data failed\n");

defaults:
	if (sdp->wce_default_on) {
		sd_first_printk(KERN_NOTICE, sdkp,
				"Assuming drive cache: write back\n");
		sdkp->WCE = 1;
	} else {
		sd_first_printk(KERN_ERR, sdkp,
				"Assuming drive cache: write through\n");
		sdkp->WCE = 0;
	}
	sdkp->RCD = 0;
	sdkp->DPOFUA = 0;
}