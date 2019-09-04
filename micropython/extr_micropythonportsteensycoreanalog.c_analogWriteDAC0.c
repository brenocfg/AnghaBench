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

void analogWriteDAC0(int val)
{
#if defined(__MK20DX256__)
	SIM_SCGC2 |= SIM_SCGC2_DAC0;
	if (analog_reference_internal) {
		DAC0_C0 = DAC_C0_DACEN;  // 1.2V ref is DACREF_1
	} else {
		DAC0_C0 = DAC_C0_DACEN | DAC_C0_DACRFS; // 3.3V VDDA is DACREF_2
	}
	if (val < 0) val = 0;  // TODO: saturate instruction?
	else if (val > 4095) val = 4095;
	*(int16_t *)&(DAC0_DAT0L) = val;
#endif
}