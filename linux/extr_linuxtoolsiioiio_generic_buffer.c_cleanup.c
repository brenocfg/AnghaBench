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

/* Variables and functions */
 scalar_t__ AUTOCHANNELS_ACTIVE ; 
 scalar_t__ AUTOCHANNELS_DISABLED ; 
 scalar_t__ autochannels ; 
 scalar_t__ buf_dir_name ; 
 int current_trigger_set ; 
 scalar_t__ dev_dir_name ; 
 int enable_disable_all_channels (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int write_sysfs_int (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int write_sysfs_string (char*,scalar_t__,char*) ; 

void cleanup(void)
{
	int ret;

	/* Disable trigger */
	if (dev_dir_name && current_trigger_set) {
		/* Disconnect the trigger - just write a dummy name. */
		ret = write_sysfs_string("trigger/current_trigger",
					 dev_dir_name, "NULL");
		if (ret < 0)
			fprintf(stderr, "Failed to disable trigger: %s\n",
				strerror(-ret));
		current_trigger_set = false;
	}

	/* Disable buffer */
	if (buf_dir_name) {
		ret = write_sysfs_int("enable", buf_dir_name, 0);
		if (ret < 0)
			fprintf(stderr, "Failed to disable buffer: %s\n",
				strerror(-ret));
	}

	/* Disable channels if auto-enabled */
	if (dev_dir_name && autochannels == AUTOCHANNELS_ACTIVE) {
		ret = enable_disable_all_channels(dev_dir_name, 0);
		if (ret)
			fprintf(stderr, "Failed to disable all channels\n");
		autochannels = AUTOCHANNELS_DISABLED;
	}
}