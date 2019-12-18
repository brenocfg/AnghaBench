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
 int I2S_SF_SCLKDIV_1 ; 
 int I2S_SF_SCLKDIV_3 ; 
 int I2S_SF_SCLKDIV_OTHER (int) ; 

__attribute__((used)) static inline int i2s_sf_sclkdiv(int div, int *out)
{
	int d;

	switch(div) {
	case 1: *out |= I2S_SF_SCLKDIV_1; return 0;
	case 3: *out |= I2S_SF_SCLKDIV_3; return 0;
	default:
		if (div%2) return -1;
		d = div/2-1;
		if (d == 8 || d == 9) return -1;
		*out |= I2S_SF_SCLKDIV_OTHER(div);
		return 0;
	}
}