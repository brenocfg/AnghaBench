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
struct sci_base_state_machine {int current_state_id; } ;
struct isci_remote_device {struct sci_base_state_machine sm; } ;
typedef  enum sci_remote_device_states { ____Placeholder_sci_remote_device_states } sci_remote_device_states ;

/* Variables and functions */
#define  SCI_DEV_READY 135 
#define  SCI_SMP_DEV_CMD 134 
#define  SCI_SMP_DEV_IDLE 133 
#define  SCI_STP_DEV_AWAIT_RESET 132 
#define  SCI_STP_DEV_CMD 131 
#define  SCI_STP_DEV_IDLE 130 
#define  SCI_STP_DEV_NCQ 129 
#define  SCI_STP_DEV_NCQ_ERROR 128 

__attribute__((used)) static bool is_remote_device_ready(struct isci_remote_device *idev)
{

	struct sci_base_state_machine *sm = &idev->sm;
	enum sci_remote_device_states state = sm->current_state_id;

	switch (state) {
	case SCI_DEV_READY:
	case SCI_STP_DEV_IDLE:
	case SCI_STP_DEV_CMD:
	case SCI_STP_DEV_NCQ:
	case SCI_STP_DEV_NCQ_ERROR:
	case SCI_STP_DEV_AWAIT_RESET:
	case SCI_SMP_DEV_IDLE:
	case SCI_SMP_DEV_CMD:
		return true;
	default:
		return false;
	}
}