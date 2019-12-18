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
struct madera {int type; } ;

/* Variables and functions */
#define  CS47L35 130 
#define  CS47L85 129 
 int EINVAL ; 
#define  WM1840 128 
 int madera_get_legacy_dspclk_setting (struct madera*,unsigned int) ; 

__attribute__((used)) static int madera_get_dspclk_setting(struct madera *madera,
				     unsigned int freq,
				     unsigned int *clock_2_val)
{
	switch (madera->type) {
	case CS47L35:
	case CS47L85:
	case WM1840:
		*clock_2_val = 0; /* don't use MADERA_DSP_CLOCK_2 */
		return madera_get_legacy_dspclk_setting(madera, freq);
	default:
		if (freq > 150000000)
			return -EINVAL;

		/* Use new exact frequency control */
		*clock_2_val = freq / 15625; /* freq * (2^6) / (10^6) */
		return 0;
	}
}