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
 unsigned int GI_SRC_SEL (unsigned int) ; 
#define  NI_GPCT_ANALOG_TRIGGER_OUT_CLOCK_SRC_BITS 136 
 unsigned int NI_GPCT_CLOCK_SRC_SELECT_MASK ; 
#define  NI_GPCT_LOGIC_LOW_CLOCK_SRC_BITS 135 
#define  NI_GPCT_NEXT_GATE_CLOCK_SRC_BITS 134 
#define  NI_GPCT_NEXT_TC_CLOCK_SRC_BITS 133 
 unsigned int NI_GPCT_PFI_CLOCK_SRC_BITS (unsigned int) ; 
#define  NI_GPCT_PXI10_CLOCK_SRC_BITS 132 
#define  NI_GPCT_PXI_STAR_TRIGGER_CLOCK_SRC_BITS 131 
 unsigned int NI_GPCT_RTSI_CLOCK_SRC_BITS (unsigned int) ; 
#define  NI_GPCT_TIMEBASE_1_CLOCK_SRC_BITS 130 
#define  NI_GPCT_TIMEBASE_2_CLOCK_SRC_BITS 129 
#define  NI_GPCT_TIMEBASE_3_CLOCK_SRC_BITS 128 
 unsigned int NI_M_ANALOG_TRIGGER_OUT_CLK ; 
 unsigned int NI_M_LOGIC_LOW_CLK ; 
 unsigned int NI_M_MAX_PFI_CHAN ; 
 unsigned int NI_M_MAX_RTSI_CHAN ; 
 unsigned int NI_M_NEXT_GATE_CLK ; 
 unsigned int NI_M_NEXT_TC_CLK ; 
 unsigned int NI_M_PFI_CLK (unsigned int) ; 
 unsigned int NI_M_PXI10_CLK ; 
 unsigned int NI_M_PXI_STAR_TRIGGER_CLK ; 
 unsigned int NI_M_RTSI_CLK (unsigned int) ; 
 unsigned int NI_M_TIMEBASE_1_CLK ; 
 unsigned int NI_M_TIMEBASE_2_CLK ; 
 unsigned int NI_M_TIMEBASE_3_CLK ; 

__attribute__((used)) static int ni_m_clk_src(unsigned int clock_source, unsigned int *bits)
{
	unsigned int clk_src = clock_source & NI_GPCT_CLOCK_SRC_SELECT_MASK;
	unsigned int ni_m_series_clock;
	unsigned int i;

	switch (clk_src) {
	case NI_GPCT_TIMEBASE_1_CLOCK_SRC_BITS:
		ni_m_series_clock = NI_M_TIMEBASE_1_CLK;
		break;
	case NI_GPCT_TIMEBASE_2_CLOCK_SRC_BITS:
		ni_m_series_clock = NI_M_TIMEBASE_2_CLK;
		break;
	case NI_GPCT_TIMEBASE_3_CLOCK_SRC_BITS:
		ni_m_series_clock = NI_M_TIMEBASE_3_CLK;
		break;
	case NI_GPCT_LOGIC_LOW_CLOCK_SRC_BITS:
		ni_m_series_clock = NI_M_LOGIC_LOW_CLK;
		break;
	case NI_GPCT_NEXT_GATE_CLOCK_SRC_BITS:
		ni_m_series_clock = NI_M_NEXT_GATE_CLK;
		break;
	case NI_GPCT_NEXT_TC_CLOCK_SRC_BITS:
		ni_m_series_clock = NI_M_NEXT_TC_CLK;
		break;
	case NI_GPCT_PXI10_CLOCK_SRC_BITS:
		ni_m_series_clock = NI_M_PXI10_CLK;
		break;
	case NI_GPCT_PXI_STAR_TRIGGER_CLOCK_SRC_BITS:
		ni_m_series_clock = NI_M_PXI_STAR_TRIGGER_CLK;
		break;
	case NI_GPCT_ANALOG_TRIGGER_OUT_CLOCK_SRC_BITS:
		ni_m_series_clock = NI_M_ANALOG_TRIGGER_OUT_CLK;
		break;
	default:
		for (i = 0; i <= NI_M_MAX_RTSI_CHAN; ++i) {
			if (clk_src == NI_GPCT_RTSI_CLOCK_SRC_BITS(i)) {
				ni_m_series_clock = NI_M_RTSI_CLK(i);
				break;
			}
		}
		if (i <= NI_M_MAX_RTSI_CHAN)
			break;
		for (i = 0; i <= NI_M_MAX_PFI_CHAN; ++i) {
			if (clk_src == NI_GPCT_PFI_CLOCK_SRC_BITS(i)) {
				ni_m_series_clock = NI_M_PFI_CLK(i);
				break;
			}
		}
		if (i <= NI_M_MAX_PFI_CHAN)
			break;
		return -EINVAL;
	}
	*bits = GI_SRC_SEL(ni_m_series_clock);
	return 0;
}