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
struct scsi_sense_hdr {int sense_key; int asc; int ascq; } ;
struct scsi_device {int dummy; } ;
struct hp_sw_dh_data {int /*<<< orphan*/  path_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HP_SW_NAME ; 
 int /*<<< orphan*/  HP_SW_PATH_PASSIVE ; 
 int /*<<< orphan*/  KERN_WARNING ; 
#define  NOT_READY 129 
 int SCSI_DH_IMM_RETRY ; 
 int SCSI_DH_IO ; 
 int SCSI_DH_OK ; 
#define  UNIT_ATTENTION 128 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int tur_done(struct scsi_device *sdev, struct hp_sw_dh_data *h,
		    struct scsi_sense_hdr *sshdr)
{
	int ret = SCSI_DH_IO;

	switch (sshdr->sense_key) {
	case UNIT_ATTENTION:
		ret = SCSI_DH_IMM_RETRY;
		break;
	case NOT_READY:
		if (sshdr->asc == 0x04 && sshdr->ascq == 2) {
			/*
			 * LUN not ready - Initialization command required
			 *
			 * This is the passive path
			 */
			h->path_state = HP_SW_PATH_PASSIVE;
			ret = SCSI_DH_OK;
			break;
		}
		/* Fallthrough */
	default:
		sdev_printk(KERN_WARNING, sdev,
			   "%s: sending tur failed, sense %x/%x/%x\n",
			   HP_SW_NAME, sshdr->sense_key, sshdr->asc,
			   sshdr->ascq);
		break;
	}
	return ret;
}