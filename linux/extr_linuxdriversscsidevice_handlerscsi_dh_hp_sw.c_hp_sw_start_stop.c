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
typedef  int u64 ;
struct scsi_sense_hdr {int sense_key; int asc; int ascq; } ;
struct scsi_device {int dummy; } ;
struct hp_sw_dh_data {struct scsi_device* sdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 int /*<<< orphan*/  HP_SW_NAME ; 
 int HP_SW_RETRIES ; 
 int /*<<< orphan*/  HP_SW_TIMEOUT ; 
 int /*<<< orphan*/  KERN_WARNING ; 
#define  NOT_READY 128 
 int REQ_FAILFAST_DEV ; 
 int REQ_FAILFAST_DRIVER ; 
 int REQ_FAILFAST_TRANSPORT ; 
 int SCSI_DH_IO ; 
 int SCSI_DH_OK ; 
 int SCSI_DH_RETRY ; 
 int START_STOP ; 
 int scsi_execute (struct scsi_device*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct scsi_sense_hdr*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_sense_valid (struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int hp_sw_start_stop(struct hp_sw_dh_data *h)
{
	unsigned char cmd[6] = { START_STOP, 0, 0, 0, 1, 0 };
	struct scsi_sense_hdr sshdr;
	struct scsi_device *sdev = h->sdev;
	int res, rc = SCSI_DH_OK;
	int retry_cnt = HP_SW_RETRIES;
	u64 req_flags = REQ_FAILFAST_DEV | REQ_FAILFAST_TRANSPORT |
		REQ_FAILFAST_DRIVER;

retry:
	res = scsi_execute(sdev, cmd, DMA_NONE, NULL, 0, NULL, &sshdr,
			HP_SW_TIMEOUT, HP_SW_RETRIES, req_flags, 0, NULL);
	if (res) {
		if (!scsi_sense_valid(&sshdr)) {
			sdev_printk(KERN_WARNING, sdev,
				    "%s: sending start_stop_unit failed, "
				    "no sense available\n", HP_SW_NAME);
			return SCSI_DH_IO;
		}
		switch (sshdr.sense_key) {
		case NOT_READY:
			if (sshdr.asc == 0x04 && sshdr.ascq == 3) {
				/*
				 * LUN not ready - manual intervention required
				 *
				 * Switch-over in progress, retry.
				 */
				if (--retry_cnt)
					goto retry;
				rc = SCSI_DH_RETRY;
				break;
			}
			/* fall through */
		default:
			sdev_printk(KERN_WARNING, sdev,
				    "%s: sending start_stop_unit failed, "
				    "sense %x/%x/%x\n", HP_SW_NAME,
				    sshdr.sense_key, sshdr.asc, sshdr.ascq);
			rc = SCSI_DH_IO;
		}
	}
	return rc;
}