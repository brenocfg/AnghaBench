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
 int /*<<< orphan*/  GOSSIP_DEV_DEBUG ; 
 int /*<<< orphan*/  ORANGEFS_REQDEVICE_NAME ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ orangefs_dev_major ; 
 int /*<<< orphan*/  orangefs_devreq_file_operations ; 
 scalar_t__ register_chrdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int orangefs_dev_init(void)
{
	/* register orangefs-req device  */
	orangefs_dev_major = register_chrdev(0,
					  ORANGEFS_REQDEVICE_NAME,
					  &orangefs_devreq_file_operations);
	if (orangefs_dev_major < 0) {
		gossip_debug(GOSSIP_DEV_DEBUG,
			     "Failed to register /dev/%s (error %d)\n",
			     ORANGEFS_REQDEVICE_NAME, orangefs_dev_major);
		return orangefs_dev_major;
	}

	gossip_debug(GOSSIP_DEV_DEBUG,
		     "*** /dev/%s character device registered ***\n",
		     ORANGEFS_REQDEVICE_NAME);
	gossip_debug(GOSSIP_DEV_DEBUG, "'mknod /dev/%s c %d 0'.\n",
		     ORANGEFS_REQDEVICE_NAME, orangefs_dev_major);
	return 0;
}