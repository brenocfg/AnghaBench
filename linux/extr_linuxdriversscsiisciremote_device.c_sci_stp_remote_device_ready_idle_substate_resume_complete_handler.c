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
struct TYPE_4__ {scalar_t__ previous_state_id; } ;
struct isci_remote_device {TYPE_2__ sm; TYPE_1__* owning_port; } ;
struct isci_host {int dummy; } ;
struct TYPE_3__ {struct isci_host* owning_controller; } ;

/* Variables and functions */
 scalar_t__ SCI_STP_DEV_NCQ ; 
 int /*<<< orphan*/  isci_remote_device_ready (struct isci_host*,struct isci_remote_device*) ; 

__attribute__((used)) static void sci_stp_remote_device_ready_idle_substate_resume_complete_handler(void *_dev)
{
	struct isci_remote_device *idev = _dev;
	struct isci_host *ihost = idev->owning_port->owning_controller;

	/* For NCQ operation we do not issue a isci_remote_device_not_ready().
	 * As a result, avoid sending the ready notification.
	 */
	if (idev->sm.previous_state_id != SCI_STP_DEV_NCQ)
		isci_remote_device_ready(ihost, idev);
}