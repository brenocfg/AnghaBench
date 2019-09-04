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
typedef  enum iwl_mvm_tdls_cs_state { ____Placeholder_iwl_mvm_tdls_cs_state } iwl_mvm_tdls_cs_state ;

/* Variables and functions */
#define  IWL_MVM_TDLS_SW_ACTIVE 132 
#define  IWL_MVM_TDLS_SW_IDLE 131 
#define  IWL_MVM_TDLS_SW_REQ_RCVD 130 
#define  IWL_MVM_TDLS_SW_REQ_SENT 129 
#define  IWL_MVM_TDLS_SW_RESP_RCVD 128 

__attribute__((used)) static const char *
iwl_mvm_tdls_cs_state_str(enum iwl_mvm_tdls_cs_state state)
{
	switch (state) {
	case IWL_MVM_TDLS_SW_IDLE:
		return "IDLE";
	case IWL_MVM_TDLS_SW_REQ_SENT:
		return "REQ SENT";
	case IWL_MVM_TDLS_SW_RESP_RCVD:
		return "RESP RECEIVED";
	case IWL_MVM_TDLS_SW_REQ_RCVD:
		return "REQ RECEIVED";
	case IWL_MVM_TDLS_SW_ACTIVE:
		return "ACTIVE";
	}

	return NULL;
}