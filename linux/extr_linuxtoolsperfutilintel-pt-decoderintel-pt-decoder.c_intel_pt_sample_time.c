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
typedef  enum intel_pt_pkt_state { ____Placeholder_intel_pt_pkt_state } intel_pt_pkt_state ;

/* Variables and functions */
#define  INTEL_PT_STATE_ERR_RESYNC 136 
#define  INTEL_PT_STATE_FUP 135 
#define  INTEL_PT_STATE_FUP_NO_TIP 134 
#define  INTEL_PT_STATE_IN_SYNC 133 
#define  INTEL_PT_STATE_NO_IP 132 
#define  INTEL_PT_STATE_NO_PSB 131 
#define  INTEL_PT_STATE_TIP 130 
#define  INTEL_PT_STATE_TIP_PGD 129 
#define  INTEL_PT_STATE_TNT 128 

__attribute__((used)) static inline bool intel_pt_sample_time(enum intel_pt_pkt_state pkt_state)
{
	switch (pkt_state) {
	case INTEL_PT_STATE_NO_PSB:
	case INTEL_PT_STATE_NO_IP:
	case INTEL_PT_STATE_ERR_RESYNC:
	case INTEL_PT_STATE_IN_SYNC:
	case INTEL_PT_STATE_TNT:
		return true;
	case INTEL_PT_STATE_TIP:
	case INTEL_PT_STATE_TIP_PGD:
	case INTEL_PT_STATE_FUP:
	case INTEL_PT_STATE_FUP_NO_TIP:
		return false;
	default:
		return true;
	};
}