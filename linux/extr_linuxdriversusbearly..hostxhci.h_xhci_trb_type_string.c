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
typedef  int u8 ;

/* Variables and functions */
#define  TRB_ADDR_DEV 160 
#define  TRB_BANDWIDTH_EVENT 159 
#define  TRB_CMD_NOOP 158 
#define  TRB_COMPLETION 157 
#define  TRB_CONFIG_EP 156 
#define  TRB_DATA 155 
#define  TRB_DEV_NOTE 154 
#define  TRB_DISABLE_SLOT 153 
#define  TRB_DOORBELL 152 
#define  TRB_ENABLE_SLOT 151 
#define  TRB_EVAL_CONTEXT 150 
#define  TRB_EVENT_DATA 149 
#define  TRB_FORCE_EVENT 148 
#define  TRB_FORCE_HEADER 147 
#define  TRB_GET_BW 146 
#define  TRB_HC_EVENT 145 
#define  TRB_ISOC 144 
#define  TRB_LINK 143 
#define  TRB_MFINDEX_WRAP 142 
#define  TRB_NEC_CMD_COMP 141 
#define  TRB_NEC_GET_FW 140 
#define  TRB_NEG_BANDWIDTH 139 
#define  TRB_NORMAL 138 
#define  TRB_PORT_STATUS 137 
#define  TRB_RESET_DEV 136 
#define  TRB_RESET_EP 135 
#define  TRB_SETUP 134 
#define  TRB_SET_DEQ 133 
#define  TRB_SET_LT 132 
#define  TRB_STATUS 131 
#define  TRB_STOP_RING 130 
#define  TRB_TRANSFER 129 
#define  TRB_TR_NOOP 128 

__attribute__((used)) static inline const char *xhci_trb_type_string(u8 type)
{
	switch (type) {
	case TRB_NORMAL:
		return "Normal";
	case TRB_SETUP:
		return "Setup Stage";
	case TRB_DATA:
		return "Data Stage";
	case TRB_STATUS:
		return "Status Stage";
	case TRB_ISOC:
		return "Isoch";
	case TRB_LINK:
		return "Link";
	case TRB_EVENT_DATA:
		return "Event Data";
	case TRB_TR_NOOP:
		return "No-Op";
	case TRB_ENABLE_SLOT:
		return "Enable Slot Command";
	case TRB_DISABLE_SLOT:
		return "Disable Slot Command";
	case TRB_ADDR_DEV:
		return "Address Device Command";
	case TRB_CONFIG_EP:
		return "Configure Endpoint Command";
	case TRB_EVAL_CONTEXT:
		return "Evaluate Context Command";
	case TRB_RESET_EP:
		return "Reset Endpoint Command";
	case TRB_STOP_RING:
		return "Stop Ring Command";
	case TRB_SET_DEQ:
		return "Set TR Dequeue Pointer Command";
	case TRB_RESET_DEV:
		return "Reset Device Command";
	case TRB_FORCE_EVENT:
		return "Force Event Command";
	case TRB_NEG_BANDWIDTH:
		return "Negotiate Bandwidth Command";
	case TRB_SET_LT:
		return "Set Latency Tolerance Value Command";
	case TRB_GET_BW:
		return "Get Port Bandwidth Command";
	case TRB_FORCE_HEADER:
		return "Force Header Command";
	case TRB_CMD_NOOP:
		return "No-Op Command";
	case TRB_TRANSFER:
		return "Transfer Event";
	case TRB_COMPLETION:
		return "Command Completion Event";
	case TRB_PORT_STATUS:
		return "Port Status Change Event";
	case TRB_BANDWIDTH_EVENT:
		return "Bandwidth Request Event";
	case TRB_DOORBELL:
		return "Doorbell Event";
	case TRB_HC_EVENT:
		return "Host Controller Event";
	case TRB_DEV_NOTE:
		return "Device Notification Event";
	case TRB_MFINDEX_WRAP:
		return "MFINDEX Wrap Event";
	case TRB_NEC_CMD_COMP:
		return "NEC Command Completion Event";
	case TRB_NEC_GET_FW:
		return "NET Get Firmware Revision Command";
	default:
		return "UNKNOWN";
	}
}