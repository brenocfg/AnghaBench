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
typedef  int uint8_t ;

/* Variables and functions */
 int gfmul (int,int) ; 

__attribute__((used)) static uint8_t gfpow(uint8_t a, int b)
{
	uint8_t v = 1;

	b %= 255;
	if (b < 0)
		b += 255;

	while (b) {
		if (b & 1)
			v = gfmul(v, a);
		a = gfmul(a, a);
		b >>= 1;
	}

	return v;
}