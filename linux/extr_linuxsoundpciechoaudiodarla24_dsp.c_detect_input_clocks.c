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
typedef  int u32 ;
struct echoaudio {TYPE_1__* comm_page; } ;
struct TYPE_2__ {int /*<<< orphan*/  status_clocks; } ;

/* Variables and functions */
 int ECHO_CLOCK_BIT_ESYNC ; 
 int ECHO_CLOCK_BIT_INTERNAL ; 
 int GLDM_CLOCK_DETECT_BIT_ESYNC ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 detect_input_clocks(const struct echoaudio *chip)
{
	u32 clocks_from_dsp, clock_bits;

	/* Map the DSP clock detect bits to the generic driver clock
	   detect bits */
	clocks_from_dsp = le32_to_cpu(chip->comm_page->status_clocks);

	clock_bits = ECHO_CLOCK_BIT_INTERNAL;

	if (clocks_from_dsp & GLDM_CLOCK_DETECT_BIT_ESYNC)
		clock_bits |= ECHO_CLOCK_BIT_ESYNC;

	return clock_bits;
}