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
 scalar_t__ g450_cmppll (struct matrox_fb_info*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  g450_setpll (struct matrox_fb_info*,unsigned int,unsigned int) ; 

void matroxfb_g450_setpll_cond(struct matrox_fb_info *minfo, unsigned int mnp,
			       unsigned int pll)
{
	if (g450_cmppll(minfo, mnp, pll)) {
		g450_setpll(minfo, mnp, pll);
	}
}