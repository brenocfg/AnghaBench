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
#define  DWC3_DEPCMD_CLEARSTALL 136 
#define  DWC3_DEPCMD_DEPSTARTCFG 135 
#define  DWC3_DEPCMD_ENDTRANSFER 134 
#define  DWC3_DEPCMD_GETEPSTATE 133 
#define  DWC3_DEPCMD_SETEPCONFIG 132 
#define  DWC3_DEPCMD_SETSTALL 131 
#define  DWC3_DEPCMD_SETTRANSFRESOURCE 130 
#define  DWC3_DEPCMD_STARTTRANSFER 129 
#define  DWC3_DEPCMD_UPDATETRANSFER 128 

__attribute__((used)) static inline const char *
dwc3_gadget_ep_cmd_string(u8 cmd)
{
	switch (cmd) {
	case DWC3_DEPCMD_DEPSTARTCFG:
		return "Start New Configuration";
	case DWC3_DEPCMD_ENDTRANSFER:
		return "End Transfer";
	case DWC3_DEPCMD_UPDATETRANSFER:
		return "Update Transfer";
	case DWC3_DEPCMD_STARTTRANSFER:
		return "Start Transfer";
	case DWC3_DEPCMD_CLEARSTALL:
		return "Clear Stall";
	case DWC3_DEPCMD_SETSTALL:
		return "Set Stall";
	case DWC3_DEPCMD_GETEPSTATE:
		return "Get Endpoint State";
	case DWC3_DEPCMD_SETTRANSFRESOURCE:
		return "Set Endpoint Transfer Resource";
	case DWC3_DEPCMD_SETEPCONFIG:
		return "Set Endpoint Configuration";
	default:
		return "UNKNOWN command";
	}
}