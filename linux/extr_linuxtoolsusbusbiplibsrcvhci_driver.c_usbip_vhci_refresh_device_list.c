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
 int /*<<< orphan*/  dbg (char*) ; 
 scalar_t__ refresh_imported_device_list () ; 

int usbip_vhci_refresh_device_list(void)
{

	if (refresh_imported_device_list())
		goto err;

	return 0;
err:
	dbg("failed to refresh device list");
	return -1;
}