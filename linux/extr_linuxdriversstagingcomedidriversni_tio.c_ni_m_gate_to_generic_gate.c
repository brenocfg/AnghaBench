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
 int EINVAL ; 
 unsigned int NI_GPCT_AI_START1_GATE_SELECT ; 
 unsigned int NI_GPCT_AI_START2_GATE_SELECT ; 
 unsigned int NI_GPCT_ANALOG_TRIGGER_OUT_GATE_SELECT ; 
 unsigned int NI_GPCT_LOGIC_LOW_GATE_SELECT ; 
 unsigned int NI_GPCT_NEXT_OUT_GATE_SELECT ; 
 unsigned int NI_GPCT_NEXT_SOURCE_GATE_SELECT ; 
 unsigned int NI_GPCT_PFI_GATE_SELECT (unsigned int) ; 
 unsigned int NI_GPCT_PXI_STAR_TRIGGER_GATE_SELECT ; 
 unsigned int NI_GPCT_RTSI_GATE_SELECT (unsigned int) ; 
 unsigned int NI_GPCT_TIMESTAMP_MUX_GATE_SELECT ; 
#define  NI_M_AI_START1_GATE_SEL 135 
#define  NI_M_AI_START2_GATE_SEL 134 
#define  NI_M_ANALOG_TRIG_OUT_GATE_SEL 133 
#define  NI_M_LOGIC_LOW_GATE_SEL 132 
 unsigned int NI_M_MAX_PFI_CHAN ; 
 unsigned int NI_M_MAX_RTSI_CHAN ; 
#define  NI_M_NEXT_OUT_GATE_SEL 131 
#define  NI_M_NEXT_SRC_GATE_SEL 130 
 unsigned int NI_M_PFI_GATE_SEL (unsigned int) ; 
#define  NI_M_PXI_STAR_TRIGGER_GATE_SEL 129 
 unsigned int NI_M_RTSI_GATE_SEL (unsigned int) ; 
#define  NI_M_TIMESTAMP_MUX_GATE_SEL 128 

__attribute__((used)) static int ni_m_gate_to_generic_gate(unsigned int gate, unsigned int *src)
{
	unsigned int source;
	unsigned int i;

	switch (gate) {
	case NI_M_TIMESTAMP_MUX_GATE_SEL:
		source = NI_GPCT_TIMESTAMP_MUX_GATE_SELECT;
		break;
	case NI_M_AI_START2_GATE_SEL:
		source = NI_GPCT_AI_START2_GATE_SELECT;
		break;
	case NI_M_PXI_STAR_TRIGGER_GATE_SEL:
		source = NI_GPCT_PXI_STAR_TRIGGER_GATE_SELECT;
		break;
	case NI_M_NEXT_OUT_GATE_SEL:
		source = NI_GPCT_NEXT_OUT_GATE_SELECT;
		break;
	case NI_M_AI_START1_GATE_SEL:
		source = NI_GPCT_AI_START1_GATE_SELECT;
		break;
	case NI_M_NEXT_SRC_GATE_SEL:
		source = NI_GPCT_NEXT_SOURCE_GATE_SELECT;
		break;
	case NI_M_ANALOG_TRIG_OUT_GATE_SEL:
		source = NI_GPCT_ANALOG_TRIGGER_OUT_GATE_SELECT;
		break;
	case NI_M_LOGIC_LOW_GATE_SEL:
		source = NI_GPCT_LOGIC_LOW_GATE_SELECT;
		break;
	default:
		for (i = 0; i <= NI_M_MAX_RTSI_CHAN; ++i) {
			if (gate == NI_M_RTSI_GATE_SEL(i)) {
				source = NI_GPCT_RTSI_GATE_SELECT(i);
				break;
			}
		}
		if (i <= NI_M_MAX_RTSI_CHAN)
			break;
		for (i = 0; i <= NI_M_MAX_PFI_CHAN; ++i) {
			if (gate == NI_M_PFI_GATE_SEL(i)) {
				source = NI_GPCT_PFI_GATE_SELECT(i);
				break;
			}
		}
		if (i <= NI_M_MAX_PFI_CHAN)
			break;
		return -EINVAL;
	}
	*src = source;
	return 0;
}