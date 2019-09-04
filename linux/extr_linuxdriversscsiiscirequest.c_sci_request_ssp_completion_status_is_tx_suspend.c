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
#define  SCU_TASK_DONE_LF_ERR 138 
#define  SCU_TASK_DONE_TX_RAW_CMD_ERR 137 
#define  SCU_TASK_OPEN_REJECT_BAD_DESTINATION 136 
#define  SCU_TASK_OPEN_REJECT_CONNECTION_RATE_NOT_SUPPORTED 135 
#define  SCU_TASK_OPEN_REJECT_PROTOCOL_NOT_SUPPORTED 134 
#define  SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_1 133 
#define  SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_2 132 
#define  SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_3 131 
#define  SCU_TASK_OPEN_REJECT_STP_RESOURCES_BUSY 130 
#define  SCU_TASK_OPEN_REJECT_WRONG_DESTINATION 129 
#define  SCU_TASK_OPEN_REJECT_ZONE_VIOLATION 128 

__attribute__((used)) static int sci_request_ssp_completion_status_is_tx_suspend(
	unsigned int completion_status)
{
	switch (completion_status) {
	case SCU_TASK_DONE_TX_RAW_CMD_ERR:
	case SCU_TASK_DONE_LF_ERR:
	case SCU_TASK_OPEN_REJECT_WRONG_DESTINATION:
	case SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_1:
	case SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_2:
	case SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_3:
	case SCU_TASK_OPEN_REJECT_BAD_DESTINATION:
	case SCU_TASK_OPEN_REJECT_ZONE_VIOLATION:
	case SCU_TASK_OPEN_REJECT_STP_RESOURCES_BUSY:
	case SCU_TASK_OPEN_REJECT_PROTOCOL_NOT_SUPPORTED:
	case SCU_TASK_OPEN_REJECT_CONNECTION_RATE_NOT_SUPPORTED:
		return 1;
	}
	return 0;
}