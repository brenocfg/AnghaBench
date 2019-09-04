#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct halmac_scan_state_set {scalar_t__ scan_cmd_construct_state; } ;
struct TYPE_2__ {struct halmac_scan_state_set scan_state_set; } ;
struct halmac_adapter {TYPE_1__ halmac_state; } ;
typedef  enum halmac_scan_cmd_construct_state { ____Placeholder_halmac_scan_cmd_construct_state } halmac_scan_cmd_construct_state ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int HALMAC_RET_ERROR_STATE ; 
 int HALMAC_RET_SUCCESS ; 
 scalar_t__ HALMAC_SCAN_CMD_CONSTRUCT_BUFFER_CLEARED ; 
 scalar_t__ HALMAC_SCAN_CMD_CONSTRUCT_CONSTRUCTING ; 
 scalar_t__ HALMAC_SCAN_CMD_CONSTRUCT_H2C_SENT ; 
 int HALMAC_SCAN_CMD_CONSTRUCT_IDLE ; 

enum halmac_ret_status halmac_transition_scan_state_88xx(
	struct halmac_adapter *halmac_adapter,
	enum halmac_scan_cmd_construct_state dest_state)
{
	struct halmac_scan_state_set *scan =
		&halmac_adapter->halmac_state.scan_state_set;

	if (scan->scan_cmd_construct_state > HALMAC_SCAN_CMD_CONSTRUCT_H2C_SENT)
		return HALMAC_RET_ERROR_STATE;

	if (dest_state == HALMAC_SCAN_CMD_CONSTRUCT_IDLE) {
		if (scan->scan_cmd_construct_state ==
			    HALMAC_SCAN_CMD_CONSTRUCT_BUFFER_CLEARED ||
		    scan->scan_cmd_construct_state ==
			    HALMAC_SCAN_CMD_CONSTRUCT_CONSTRUCTING)
			return HALMAC_RET_ERROR_STATE;
	} else if (dest_state == HALMAC_SCAN_CMD_CONSTRUCT_BUFFER_CLEARED) {
		if (scan->scan_cmd_construct_state ==
		    HALMAC_SCAN_CMD_CONSTRUCT_H2C_SENT)
			return HALMAC_RET_ERROR_STATE;
	} else if (dest_state == HALMAC_SCAN_CMD_CONSTRUCT_CONSTRUCTING) {
		if (scan->scan_cmd_construct_state ==
			    HALMAC_SCAN_CMD_CONSTRUCT_IDLE ||
		    scan->scan_cmd_construct_state ==
			    HALMAC_SCAN_CMD_CONSTRUCT_H2C_SENT)
			return HALMAC_RET_ERROR_STATE;
	} else if (dest_state == HALMAC_SCAN_CMD_CONSTRUCT_H2C_SENT) {
		if (scan->scan_cmd_construct_state !=
			    HALMAC_SCAN_CMD_CONSTRUCT_CONSTRUCTING &&
		    scan->scan_cmd_construct_state !=
			    HALMAC_SCAN_CMD_CONSTRUCT_BUFFER_CLEARED)
			return HALMAC_RET_ERROR_STATE;
	}

	scan->scan_cmd_construct_state = dest_state;

	return HALMAC_RET_SUCCESS;
}