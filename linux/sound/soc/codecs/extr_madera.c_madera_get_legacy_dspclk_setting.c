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
struct madera {int rev; int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  CS47L85 129 
 int EINVAL ; 
 int MADERA_DSPCLK_147MHZ ; 
 int MADERA_DSP_CLK_FREQ_LEGACY_SHIFT ; 
 int MADERA_SYSCLK_49MHZ ; 
 int MADERA_SYSCLK_FREQ_SHIFT ; 
#define  WM1840 128 

__attribute__((used)) static int madera_get_legacy_dspclk_setting(struct madera *madera,
					    unsigned int freq)
{
	switch (freq) {
	case 0:
		return 0;
	case 45158400:
	case 49152000:
		switch (madera->type) {
		case CS47L85:
		case WM1840:
			if (madera->rev < 3)
				return -EINVAL;
			else
				return MADERA_SYSCLK_49MHZ <<
				       MADERA_SYSCLK_FREQ_SHIFT;
		default:
			return -EINVAL;
		}
	case 135475200:
	case 147456000:
		return MADERA_DSPCLK_147MHZ << MADERA_DSP_CLK_FREQ_LEGACY_SHIFT;
	default:
		return -EINVAL;
	}
}