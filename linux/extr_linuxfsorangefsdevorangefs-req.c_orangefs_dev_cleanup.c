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
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  orangefs_dev_major ; 
 int /*<<< orphan*/  unregister_chrdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void orangefs_dev_cleanup(void)
{
	unregister_chrdev(orangefs_dev_major, ORANGEFS_REQDEVICE_NAME);
	gossip_debug(GOSSIP_DEV_DEBUG,
		     "*** /dev/%s character device unregistered ***\n",
		     ORANGEFS_REQDEVICE_NAME);
}