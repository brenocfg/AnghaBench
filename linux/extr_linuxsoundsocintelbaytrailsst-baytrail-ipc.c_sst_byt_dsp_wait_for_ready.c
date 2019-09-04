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
struct sst_pdata {struct sst_byt* dsp; } ;
struct sst_byt {int /*<<< orphan*/  dev; int /*<<< orphan*/  boot_complete; int /*<<< orphan*/  boot_wait; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IPC_BOOT_MSECS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sst_byt_dsp_wait_for_ready(struct device *dev, struct sst_pdata *pdata)
{
	struct sst_byt *byt = pdata->dsp;
	int err;

	dev_dbg(byt->dev, "wait for dsp reboot\n");

	err = wait_event_timeout(byt->boot_wait, byt->boot_complete,
				 msecs_to_jiffies(IPC_BOOT_MSECS));
	if (err == 0) {
		dev_err(byt->dev, "ipc: error DSP boot timeout\n");
		return -EIO;
	}

	dev_dbg(byt->dev, "dsp rebooted\n");
	return 0;
}