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
struct dasd_eckd_private {int /*<<< orphan*/ * conf_data; scalar_t__ conf_len; int /*<<< orphan*/ * gneq; int /*<<< orphan*/ * vdsneq; int /*<<< orphan*/ * sneq; int /*<<< orphan*/ * ned; } ;
struct dasd_device {TYPE_1__* path; struct dasd_eckd_private* private; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_2__ {scalar_t__ chpid; scalar_t__ ssid; scalar_t__ cssid; int /*<<< orphan*/ * conf_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dasd_alias_disconnect_device_from_lcu (struct dasd_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dasd_eckd_uncheck_device(struct dasd_device *device)
{
	struct dasd_eckd_private *private = device->private;
	int i;

	if (!private)
		return;

	dasd_alias_disconnect_device_from_lcu(device);
	private->ned = NULL;
	private->sneq = NULL;
	private->vdsneq = NULL;
	private->gneq = NULL;
	private->conf_len = 0;
	for (i = 0; i < 8; i++) {
		kfree(device->path[i].conf_data);
		if ((__u8 *)device->path[i].conf_data ==
		    private->conf_data) {
			private->conf_data = NULL;
			private->conf_len = 0;
		}
		device->path[i].conf_data = NULL;
		device->path[i].cssid = 0;
		device->path[i].ssid = 0;
		device->path[i].chpid = 0;
	}
	kfree(private->conf_data);
	private->conf_data = NULL;
}