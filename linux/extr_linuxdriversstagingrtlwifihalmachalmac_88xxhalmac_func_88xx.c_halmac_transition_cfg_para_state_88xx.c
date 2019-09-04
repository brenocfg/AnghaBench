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
struct halmac_cfg_para_state_set {scalar_t__ cfg_para_cmd_construct_state; } ;
struct TYPE_2__ {struct halmac_cfg_para_state_set cfg_para_state_set; } ;
struct halmac_adapter {TYPE_1__ halmac_state; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_cfg_para_cmd_construct_state { ____Placeholder_halmac_cfg_para_cmd_construct_state } halmac_cfg_para_cmd_construct_state ;

/* Variables and functions */
 scalar_t__ HALMAC_CFG_PARA_CMD_CONSTRUCT_CONSTRUCTING ; 
 scalar_t__ HALMAC_CFG_PARA_CMD_CONSTRUCT_H2C_SENT ; 
 scalar_t__ HALMAC_CFG_PARA_CMD_CONSTRUCT_IDLE ; 
 int HALMAC_RET_ERROR_STATE ; 
 int HALMAC_RET_SUCCESS ; 

enum halmac_ret_status halmac_transition_cfg_para_state_88xx(
	struct halmac_adapter *halmac_adapter,
	enum halmac_cfg_para_cmd_construct_state dest_state)
{
	struct halmac_cfg_para_state_set *cfg_para =
		&halmac_adapter->halmac_state.cfg_para_state_set;

	if (cfg_para->cfg_para_cmd_construct_state !=
		    HALMAC_CFG_PARA_CMD_CONSTRUCT_IDLE &&
	    cfg_para->cfg_para_cmd_construct_state !=
		    HALMAC_CFG_PARA_CMD_CONSTRUCT_CONSTRUCTING &&
	    cfg_para->cfg_para_cmd_construct_state !=
		    HALMAC_CFG_PARA_CMD_CONSTRUCT_H2C_SENT)
		return HALMAC_RET_ERROR_STATE;

	if (dest_state == HALMAC_CFG_PARA_CMD_CONSTRUCT_IDLE) {
		if (cfg_para->cfg_para_cmd_construct_state ==
		    HALMAC_CFG_PARA_CMD_CONSTRUCT_CONSTRUCTING)
			return HALMAC_RET_ERROR_STATE;
	} else if (dest_state == HALMAC_CFG_PARA_CMD_CONSTRUCT_CONSTRUCTING) {
		if (cfg_para->cfg_para_cmd_construct_state ==
		    HALMAC_CFG_PARA_CMD_CONSTRUCT_H2C_SENT)
			return HALMAC_RET_ERROR_STATE;
	} else if (dest_state == HALMAC_CFG_PARA_CMD_CONSTRUCT_H2C_SENT) {
		if (cfg_para->cfg_para_cmd_construct_state ==
			    HALMAC_CFG_PARA_CMD_CONSTRUCT_IDLE ||
		    cfg_para->cfg_para_cmd_construct_state ==
			    HALMAC_CFG_PARA_CMD_CONSTRUCT_H2C_SENT)
			return HALMAC_RET_ERROR_STATE;
	}

	cfg_para->cfg_para_cmd_construct_state = dest_state;

	return HALMAC_RET_SUCCESS;
}