#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int result; void (* scsi_done ) (struct scsi_cmnd*) ;TYPE_2__* device; } ;
struct rtsx_dev {int /*<<< orphan*/  cmnd_ready; TYPE_1__* pci; struct rtsx_chip* chip; } ;
struct rtsx_chip {struct scsi_cmnd* srb; } ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DID_NO_CONNECT ; 
 int /*<<< orphan*/  RTSX_STAT_DISCONNECT ; 
 int SCSI_MLQUEUE_HOST_BUSY ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct rtsx_dev* host_to_rtsx (int /*<<< orphan*/ ) ; 
 scalar_t__ rtsx_chk_stat (struct rtsx_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int queuecommand_lck(struct scsi_cmnd *srb,
			    void (*done)(struct scsi_cmnd *))
{
	struct rtsx_dev *dev = host_to_rtsx(srb->device->host);
	struct rtsx_chip *chip = dev->chip;

	/* check for state-transition errors */
	if (chip->srb) {
		dev_err(&dev->pci->dev, "Error: chip->srb = %p\n",
			chip->srb);
		return SCSI_MLQUEUE_HOST_BUSY;
	}

	/* fail the command if we are disconnecting */
	if (rtsx_chk_stat(chip, RTSX_STAT_DISCONNECT)) {
		dev_info(&dev->pci->dev, "Fail command during disconnect\n");
		srb->result = DID_NO_CONNECT << 16;
		done(srb);
		return 0;
	}

	/* enqueue the command and wake up the control thread */
	srb->scsi_done = done;
	chip->srb = srb;
	complete(&dev->cmnd_ready);

	return 0;
}