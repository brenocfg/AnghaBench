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
struct halmac_efuse_state_set {scalar_t__ efuse_cmd_construct_state; } ;
struct TYPE_2__ {struct halmac_efuse_state_set efuse_state_set; } ;
struct halmac_adapter {TYPE_1__ halmac_state; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_efuse_cmd_construct_state { ____Placeholder_halmac_efuse_cmd_construct_state } halmac_efuse_cmd_construct_state ;

/* Variables and functions */
 scalar_t__ HALMAC_EFUSE_CMD_CONSTRUCT_BUSY ; 
 scalar_t__ HALMAC_EFUSE_CMD_CONSTRUCT_H2C_SENT ; 
 scalar_t__ HALMAC_EFUSE_CMD_CONSTRUCT_IDLE ; 
 int HALMAC_RET_ERROR_STATE ; 
 int HALMAC_RET_SUCCESS ; 

enum halmac_ret_status halmac_transition_efuse_state_88xx(
	struct halmac_adapter *halmac_adapter,
	enum halmac_efuse_cmd_construct_state dest_state)
{
	struct halmac_efuse_state_set *efuse_state =
		&halmac_adapter->halmac_state.efuse_state_set;

	if (efuse_state->efuse_cmd_construct_state !=
		    HALMAC_EFUSE_CMD_CONSTRUCT_IDLE &&
	    efuse_state->efuse_cmd_construct_state !=
		    HALMAC_EFUSE_CMD_CONSTRUCT_BUSY &&
	    efuse_state->efuse_cmd_construct_state !=
		    HALMAC_EFUSE_CMD_CONSTRUCT_H2C_SENT)
		return HALMAC_RET_ERROR_STATE;

	if (efuse_state->efuse_cmd_construct_state == dest_state)
		return HALMAC_RET_ERROR_STATE;

	if (dest_state == HALMAC_EFUSE_CMD_CONSTRUCT_BUSY) {
		if (efuse_state->efuse_cmd_construct_state ==
		    HALMAC_EFUSE_CMD_CONSTRUCT_H2C_SENT)
			return HALMAC_RET_ERROR_STATE;
	} else if (dest_state == HALMAC_EFUSE_CMD_CONSTRUCT_H2C_SENT) {
		if (efuse_state->efuse_cmd_construct_state ==
		    HALMAC_EFUSE_CMD_CONSTRUCT_IDLE)
			return HALMAC_RET_ERROR_STATE;
	}

	efuse_state->efuse_cmd_construct_state = dest_state;

	return HALMAC_RET_SUCCESS;
}