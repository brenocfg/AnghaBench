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
struct rtsx_dev {int /*<<< orphan*/  dev_mutex; struct rtsx_chip* chip; int /*<<< orphan*/  scanning_done; int /*<<< orphan*/  delay_wait; } ;
struct rtsx_chip {TYPE_1__* srb; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {int result; int /*<<< orphan*/  (* scsi_done ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int DID_NO_CONNECT ; 
 int /*<<< orphan*/  RTSX_STAT_DISCONNECT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtsx_set_stat (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* rtsx_to_host (struct rtsx_dev*) ; 
 int /*<<< orphan*/  scsi_lock (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_unlock (struct Scsi_Host*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_timeout (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void quiesce_and_remove_host(struct rtsx_dev *dev)
{
	struct Scsi_Host *host = rtsx_to_host(dev);
	struct rtsx_chip *chip = dev->chip;

	/*
	 * Prevent new transfers, stop the current command, and
	 * interrupt a SCSI-scan or device-reset delay
	 */
	mutex_lock(&dev->dev_mutex);
	scsi_lock(host);
	rtsx_set_stat(chip, RTSX_STAT_DISCONNECT);
	scsi_unlock(host);
	mutex_unlock(&dev->dev_mutex);
	wake_up(&dev->delay_wait);
	wait_for_completion(&dev->scanning_done);

	/* Wait some time to let other threads exist */
	wait_timeout(100);

	/*
	 * queuecommand won't accept any new commands and the control
	 * thread won't execute a previously-queued command.  If there
	 * is such a command pending, complete it with an error.
	 */
	mutex_lock(&dev->dev_mutex);
	if (chip->srb) {
		chip->srb->result = DID_NO_CONNECT << 16;
		scsi_lock(host);
		chip->srb->scsi_done(dev->chip->srb);
		chip->srb = NULL;
		scsi_unlock(host);
	}
	mutex_unlock(&dev->dev_mutex);

	/* Now we own no commands so it's safe to remove the SCSI host */
	scsi_remove_host(host);
}