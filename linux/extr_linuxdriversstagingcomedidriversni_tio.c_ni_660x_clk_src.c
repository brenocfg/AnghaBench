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
 unsigned int NI_660X_LOGIC_LOW_CLK ; 
 unsigned int NI_660X_MAX_RTSI_CHAN ; 
 unsigned int NI_660X_MAX_SRC_PIN ; 
 unsigned int NI_660X_NEXT_GATE_CLK ; 
 unsigned int NI_660X_NEXT_TC_CLK ; 
 unsigned int NI_660X_RTSI_CLK (unsigned int) ; 
 unsigned int NI_660X_SRC_PIN_CLK (unsigned int) ; 
 unsigned int NI_660X_SRC_PIN_I_CLK ; 
 unsigned int NI_660X_TIMEBASE_1_CLK ; 
 unsigned int NI_660X_TIMEBASE_2_CLK ; 
 unsigned int NI_660X_TIMEBASE_3_CLK ; 
 unsigned int NI_GPCT_CLOCK_SRC_SELECT_MASK ; 
#define  NI_GPCT_LOGIC_LOW_CLOCK_SRC_BITS 134 
#define  NI_GPCT_NEXT_GATE_CLOCK_SRC_BITS 133 
#define  NI_GPCT_NEXT_TC_CLOCK_SRC_BITS 132 
 unsigned int NI_GPCT_RTSI_CLOCK_SRC_BITS (unsigned int) ; 
 unsigned int NI_GPCT_SOURCE_PIN_CLOCK_SRC_BITS (unsigned int) ; 
#define  NI_GPCT_SOURCE_PIN_i_CLOCK_SRC_BITS 131 
#define  NI_GPCT_TIMEBASE_1_CLOCK_SRC_BITS 130 
#define  NI_GPCT_TIMEBASE_2_CLOCK_SRC_BITS 129 
#define  NI_GPCT_TIMEBASE_3_CLOCK_SRC_BITS 128 

__attribute__((used)) static int ni_660x_clk_src(unsigned int clock_source, unsigned int *bits)
{
	unsigned int clk_src = clock_source & NI_GPCT_CLOCK_SRC_SELECT_MASK;
	unsigned int ni_660x_clock;
	unsigned int i;

	switch (clk_src) {
	case NI_GPCT_TIMEBASE_1_CLOCK_SRC_BITS:
		ni_660x_clock = NI_660X_TIMEBASE_1_CLK;
		break;
	case NI_GPCT_TIMEBASE_2_CLOCK_SRC_BITS:
		ni_660x_clock = NI_660X_TIMEBASE_2_CLK;
		break;
	case NI_GPCT_TIMEBASE_3_CLOCK_SRC_BITS:
		ni_660x_clock = NI_660X_TIMEBASE_3_CLK;
		break;
	case NI_GPCT_LOGIC_LOW_CLOCK_SRC_BITS:
		ni_660x_clock = NI_660X_LOGIC_LOW_CLK;
		break;
	case NI_GPCT_SOURCE_PIN_i_CLOCK_SRC_BITS:
		ni_660x_clock = NI_660X_SRC_PIN_I_CLK;
		break;
	case NI_GPCT_NEXT_GATE_CLOCK_SRC_BITS:
		ni_660x_clock = NI_660X_NEXT_GATE_CLK;
		break;
	case NI_GPCT_NEXT_TC_CLOCK_SRC_BITS:
		ni_660x_clock = NI_660X_NEXT_TC_CLK;
		break;
	default:
		for (i = 0; i <= NI_660X_MAX_RTSI_CHAN; ++i) {
			if (clk_src == NI_GPCT_RTSI_CLOCK_SRC_BITS(i)) {
				ni_660x_clock = NI_660X_RTSI_CLK(i);
				break;
			}
		}
		if (i <= NI_660X_MAX_RTSI_CHAN)
			break;
		for (i = 0; i <= NI_660X_MAX_SRC_PIN; ++i) {
			if (clk_src == NI_GPCT_SOURCE_PIN_CLOCK_SRC_BITS(i)) {
				ni_660x_clock = NI_660X_SRC_PIN_CLK(i);
				break;
			}
		}
		if (i <= NI_660X_MAX_SRC_PIN)
			break;
		return -EINVAL;
	}
	*bits = GI_SRC_SEL(ni_660x_clock);
	return 0;
}