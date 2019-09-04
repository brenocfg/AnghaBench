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
struct TYPE_2__ {int /*<<< orphan*/  pll; } ;
struct matrox_fb_info {TYPE_1__ features; } ;

/* Variables and functions */
 int matroxfb_PLL_calcclock (int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static inline int PLL_calcclock(const struct matrox_fb_info *minfo,
				unsigned int freq, unsigned int fmax,
				unsigned int *in, unsigned int *feed,
				unsigned int *post)
{
	return matroxfb_PLL_calcclock(&minfo->features.pll, freq, fmax, in, feed, post);
}