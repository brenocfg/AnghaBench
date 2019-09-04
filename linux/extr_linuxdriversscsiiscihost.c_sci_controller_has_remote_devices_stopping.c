#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct isci_host {size_t remote_node_entries; TYPE_2__** device_table; } ;
struct TYPE_3__ {scalar_t__ current_state_id; } ;
struct TYPE_4__ {TYPE_1__ sm; } ;

/* Variables and functions */
 scalar_t__ SCI_DEV_STOPPING ; 

bool sci_controller_has_remote_devices_stopping(struct isci_host *ihost)
{
	u32 index;

	for (index = 0; index < ihost->remote_node_entries; index++) {
		if ((ihost->device_table[index] != NULL) &&
		   (ihost->device_table[index]->sm.current_state_id == SCI_DEV_STOPPING))
			return true;
	}

	return false;
}