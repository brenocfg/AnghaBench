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
typedef  int u32 ;
typedef  int s32 ;

/* Variables and functions */
 unsigned char PM2_REFERENCE_CLOCK ; 

__attribute__((used)) static void pm2v_mnp(u32 clk, unsigned char *mm, unsigned char *nn,
		     unsigned char *pp)
{
	unsigned char m;
	unsigned char n;
	unsigned char p;
	u32 f;
	s32 delta = 1000;

	*mm = *nn = *pp = 0;
	for (m = 1; m < 128; m++) {
		for (n = 2 * m + 1; n; n++) {
			for (p = 0; p < 2; p++) {
				f = (PM2_REFERENCE_CLOCK >> (p + 1)) * n / m;
				if (clk > f - delta && clk < f + delta) {
					delta = (clk > f) ? clk - f : f - clk;
					*mm = m;
					*nn = n;
					*pp = p;
				}
			}
		}
	}
}