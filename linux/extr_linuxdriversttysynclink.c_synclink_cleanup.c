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
struct mgsl_struct {int /*<<< orphan*/  port; struct mgsl_struct* next_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_name ; 
 int /*<<< orphan*/  driver_version ; 
 int /*<<< orphan*/  kfree (struct mgsl_struct*) ; 
 struct mgsl_struct* mgsl_device_list ; 
 int /*<<< orphan*/  mgsl_release_resources (struct mgsl_struct*) ; 
 scalar_t__ pci_registered ; 
 int /*<<< orphan*/  pci_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,char*,int,...) ; 
 int /*<<< orphan*/  put_tty_driver (scalar_t__) ; 
 scalar_t__ serial_driver ; 
 int /*<<< orphan*/  synclink_pci_driver ; 
 int /*<<< orphan*/  tty_port_destroy (int /*<<< orphan*/ *) ; 
 int tty_unregister_driver (scalar_t__) ; 

__attribute__((used)) static void synclink_cleanup(void)
{
	int rc;
	struct mgsl_struct *info;
	struct mgsl_struct *tmp;

	printk("Unloading %s: %s\n", driver_name, driver_version);

	if (serial_driver) {
		rc = tty_unregister_driver(serial_driver);
		if (rc)
			printk("%s(%d) failed to unregister tty driver err=%d\n",
			       __FILE__,__LINE__,rc);
		put_tty_driver(serial_driver);
	}

	info = mgsl_device_list;
	while(info) {
#if SYNCLINK_GENERIC_HDLC
		hdlcdev_exit(info);
#endif
		mgsl_release_resources(info);
		tmp = info;
		info = info->next_device;
		tty_port_destroy(&tmp->port);
		kfree(tmp);
	}
	
	if (pci_registered)
		pci_unregister_driver(&synclink_pci_driver);
}