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
struct matrox_fb_info {int dummy; } ;

/* Variables and functions */
 int matroxfb_DAC_in (struct matrox_fb_info const*,unsigned int) ; 

__attribute__((used)) static inline int g450_isplllocked(const struct matrox_fb_info *minfo,
				   unsigned int regidx)
{
	unsigned int j;

	for (j = 0; j < 1000; j++) {
		if (matroxfb_DAC_in(minfo, regidx) & 0x40) {
			unsigned int r = 0;
			int i;

			for (i = 0; i < 100; i++) {
				r += matroxfb_DAC_in(minfo, regidx) & 0x40;
			}
			return r >= (90 * 0x40);
		}
		/* udelay(1)... but DAC_in is much slower... */
	}
	return 0;
}