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
struct ufs_hba {int wlun_dev_clr_ua; int curr_dev_pwr_mode; TYPE_1__* host; struct scsi_device* sdev_ufs_device; } ;
struct scsi_sense_hdr {int dummy; } ;
struct scsi_device {int dummy; } ;
typedef  enum ufs_dev_pwr_mode { ____Placeholder_ufs_dev_pwr_mode } ufs_dev_pwr_mode ;
struct TYPE_2__ {int eh_noresume; int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 scalar_t__ DRIVER_SENSE ; 
 int ENODEV ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  RQF_PM ; 
 unsigned char START_STOP ; 
 int /*<<< orphan*/  START_STOP_TIMEOUT ; 
 scalar_t__ driver_byte (int) ; 
 int scsi_device_get (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_device_online (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_device_put (struct scsi_device*) ; 
 int scsi_execute (struct scsi_device*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct scsi_sense_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_print_sense_hdr (struct scsi_device*,int /*<<< orphan*/ *,struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int ufshcd_send_request_sense (struct ufs_hba*,struct scsi_device*) ; 

__attribute__((used)) static int ufshcd_set_dev_pwr_mode(struct ufs_hba *hba,
				     enum ufs_dev_pwr_mode pwr_mode)
{
	unsigned char cmd[6] = { START_STOP };
	struct scsi_sense_hdr sshdr;
	struct scsi_device *sdp;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(hba->host->host_lock, flags);
	sdp = hba->sdev_ufs_device;
	if (sdp) {
		ret = scsi_device_get(sdp);
		if (!ret && !scsi_device_online(sdp)) {
			ret = -ENODEV;
			scsi_device_put(sdp);
		}
	} else {
		ret = -ENODEV;
	}
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	if (ret)
		return ret;

	/*
	 * If scsi commands fail, the scsi mid-layer schedules scsi error-
	 * handling, which would wait for host to be resumed. Since we know
	 * we are functional while we are here, skip host resume in error
	 * handling context.
	 */
	hba->host->eh_noresume = 1;
	if (hba->wlun_dev_clr_ua) {
		ret = ufshcd_send_request_sense(hba, sdp);
		if (ret)
			goto out;
		/* Unit attention condition is cleared now */
		hba->wlun_dev_clr_ua = false;
	}

	cmd[4] = pwr_mode << 4;

	/*
	 * Current function would be generally called from the power management
	 * callbacks hence set the RQF_PM flag so that it doesn't resume the
	 * already suspended childs.
	 */
	ret = scsi_execute(sdp, cmd, DMA_NONE, NULL, 0, NULL, &sshdr,
			START_STOP_TIMEOUT, 0, 0, RQF_PM, NULL);
	if (ret) {
		sdev_printk(KERN_WARNING, sdp,
			    "START_STOP failed for power mode: %d, result %x\n",
			    pwr_mode, ret);
		if (driver_byte(ret) == DRIVER_SENSE)
			scsi_print_sense_hdr(sdp, NULL, &sshdr);
	}

	if (!ret)
		hba->curr_dev_pwr_mode = pwr_mode;
out:
	scsi_device_put(sdp);
	hba->host->eh_noresume = 0;
	return ret;
}