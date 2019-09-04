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
struct isci_remote_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ current_state_id; } ;
struct isci_host {TYPE_2__ sm; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SCIC_STOPPING ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct isci_host*,struct isci_remote_device*,scalar_t__) ; 
 int /*<<< orphan*/  isci_host_stop_complete (struct isci_host*) ; 
 int /*<<< orphan*/  sci_controller_has_remote_devices_stopping (struct isci_host*) ; 

void sci_controller_remote_device_stopped(struct isci_host *ihost,
					  struct isci_remote_device *idev)
{
	if (ihost->sm.current_state_id != SCIC_STOPPING) {
		dev_dbg(&ihost->pdev->dev,
			"SCIC Controller 0x%p remote device stopped event "
			"from device 0x%p in unexpected state %d\n",
			ihost, idev,
			ihost->sm.current_state_id);
		return;
	}

	if (!sci_controller_has_remote_devices_stopping(ihost))
		isci_host_stop_complete(ihost);
}