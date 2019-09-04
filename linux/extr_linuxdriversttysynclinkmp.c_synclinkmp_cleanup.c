#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ port_num; int /*<<< orphan*/  port; struct TYPE_9__* next_device; scalar_t__ sca_base; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  LPR ; 
 int /*<<< orphan*/  driver_name ; 
 int /*<<< orphan*/  driver_version ; 
 int /*<<< orphan*/  free_dma_bufs (TYPE_1__*) ; 
 int /*<<< orphan*/  free_tmp_rx_buf (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,char*,int,...) ; 
 int /*<<< orphan*/  put_tty_driver (scalar_t__) ; 
 int /*<<< orphan*/  release_resources (TYPE_1__*) ; 
 int /*<<< orphan*/  reset_port (TYPE_1__*) ; 
 scalar_t__ serial_driver ; 
 TYPE_1__* synclinkmp_device_list ; 
 int /*<<< orphan*/  synclinkmp_pci_driver ; 
 int /*<<< orphan*/  tty_port_destroy (int /*<<< orphan*/ *) ; 
 int tty_unregister_driver (scalar_t__) ; 
 int /*<<< orphan*/  write_reg (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void synclinkmp_cleanup(void)
{
	int rc;
	SLMP_INFO *info;
	SLMP_INFO *tmp;

	printk("Unloading %s %s\n", driver_name, driver_version);

	if (serial_driver) {
		rc = tty_unregister_driver(serial_driver);
		if (rc)
			printk("%s(%d) failed to unregister tty driver err=%d\n",
			       __FILE__,__LINE__,rc);
		put_tty_driver(serial_driver);
	}

	/* reset devices */
	info = synclinkmp_device_list;
	while(info) {
		reset_port(info);
		info = info->next_device;
	}

	/* release devices */
	info = synclinkmp_device_list;
	while(info) {
#if SYNCLINK_GENERIC_HDLC
		hdlcdev_exit(info);
#endif
		free_dma_bufs(info);
		free_tmp_rx_buf(info);
		if ( info->port_num == 0 ) {
			if (info->sca_base)
				write_reg(info, LPR, 1); /* set low power mode */
			release_resources(info);
		}
		tmp = info;
		info = info->next_device;
		tty_port_destroy(&tmp->port);
		kfree(tmp);
	}

	pci_unregister_driver(&synclinkmp_pci_driver);
}