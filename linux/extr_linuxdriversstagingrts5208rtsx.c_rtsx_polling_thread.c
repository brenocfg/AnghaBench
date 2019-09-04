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
struct xd_info {scalar_t__ cleanup_counter; } ;
struct sd_info {scalar_t__ cleanup_counter; } ;
struct rtsx_dev {int /*<<< orphan*/  polling_exit; int /*<<< orphan*/  dev_mutex; TYPE_1__* pci; struct rtsx_chip* chip; } ;
struct ms_info {scalar_t__ cleanup_counter; } ;
struct rtsx_chip {struct ms_info ms_card; struct xd_info xd_card; struct sd_info sd_card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLLING_INTERVAL ; 
 int /*<<< orphan*/  RTSX_STAT_DISCONNECT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  complete_and_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int delay_use ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mspro_polling_format_status (struct rtsx_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rtsx_chk_stat (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_polling_func (struct rtsx_chip*) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_timeout (int) ; 

__attribute__((used)) static int rtsx_polling_thread(void *__dev)
{
	struct rtsx_dev *dev = __dev;
	struct rtsx_chip *chip = dev->chip;
	struct sd_info *sd_card = &chip->sd_card;
	struct xd_info *xd_card = &chip->xd_card;
	struct ms_info *ms_card = &chip->ms_card;

	sd_card->cleanup_counter = 0;
	xd_card->cleanup_counter = 0;
	ms_card->cleanup_counter = 0;

	/* Wait until SCSI scan finished */
	wait_timeout((delay_use + 5) * 1000);

	for (;;) {
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_timeout(msecs_to_jiffies(POLLING_INTERVAL));

		/* lock the device pointers */
		mutex_lock(&dev->dev_mutex);

		/* if the device has disconnected, we are free to exit */
		if (rtsx_chk_stat(chip, RTSX_STAT_DISCONNECT)) {
			dev_info(&dev->pci->dev, "-- rtsx-polling exiting\n");
			mutex_unlock(&dev->dev_mutex);
			break;
		}

		mutex_unlock(&dev->dev_mutex);

		mspro_polling_format_status(chip);

		/* lock the device pointers */
		mutex_lock(&dev->dev_mutex);

		rtsx_polling_func(chip);

		/* unlock the device pointers */
		mutex_unlock(&dev->dev_mutex);
	}

	complete_and_exit(&dev->polling_exit, 0);
}