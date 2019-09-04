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
#define  DWC3_DGCMD_ALL_FIFO_FLUSH 136 
#define  DWC3_DGCMD_RUN_SOC_BUS_LOOPBACK 135 
#define  DWC3_DGCMD_SELECTED_FIFO_FLUSH 134 
#define  DWC3_DGCMD_SET_ENDPOINT_NRDY 133 
#define  DWC3_DGCMD_SET_LMP 132 
#define  DWC3_DGCMD_SET_PERIODIC_PAR 131 
#define  DWC3_DGCMD_SET_SCRATCHPAD_ADDR_HI 130 
#define  DWC3_DGCMD_SET_SCRATCHPAD_ADDR_LO 129 
#define  DWC3_DGCMD_XMIT_FUNCTION 128 

__attribute__((used)) static inline const char *
dwc3_gadget_generic_cmd_string(u8 cmd)
{
	switch (cmd) {
	case DWC3_DGCMD_SET_LMP:
		return "Set LMP";
	case DWC3_DGCMD_SET_PERIODIC_PAR:
		return "Set Periodic Parameters";
	case DWC3_DGCMD_XMIT_FUNCTION:
		return "Transmit Function Wake Device Notification";
	case DWC3_DGCMD_SET_SCRATCHPAD_ADDR_LO:
		return "Set Scratchpad Buffer Array Address Lo";
	case DWC3_DGCMD_SET_SCRATCHPAD_ADDR_HI:
		return "Set Scratchpad Buffer Array Address Hi";
	case DWC3_DGCMD_SELECTED_FIFO_FLUSH:
		return "Selected FIFO Flush";
	case DWC3_DGCMD_ALL_FIFO_FLUSH:
		return "All FIFO Flush";
	case DWC3_DGCMD_SET_ENDPOINT_NRDY:
		return "Set Endpoint NRDY";
	case DWC3_DGCMD_RUN_SOC_BUS_LOOPBACK:
		return "Run SoC Bus Loopback Test";
	default:
		return "UNKNOWN";
	}
}