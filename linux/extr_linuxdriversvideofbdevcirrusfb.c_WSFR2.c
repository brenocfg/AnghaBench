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
struct cirrusfb_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void WSFR2(struct cirrusfb_info *cinfo, unsigned char val)
{
#ifdef CONFIG_ZORRO
	/* writing an arbitrary value to this one causes the monitor switcher */
	/* to flip to Amiga display */
	assert(cinfo->regbase != NULL);
	cinfo->SFR = val;
	z_writeb(val, cinfo->regbase + 0x9000);
#endif
}