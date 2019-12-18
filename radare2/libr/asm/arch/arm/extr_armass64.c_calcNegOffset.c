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
 int countTrailingZeros (int) ; 

__attribute__((used)) static int calcNegOffset(int n, int shift) {
	int a = n >> shift;
	if (a == 0) {
		return 0xff;
	}
	// find first set bit then invert it and all
	// bits below it
	int t = 0x400;
	while (!(t & a) && a != 0 && t != 0) {
		t = t >> 1;
	}
	t = t & (t - 1);
	a = a ^ t;
	// If bits below 32 are set
	if (countTrailingZeros(n) > shift) {
		a--;
	}
	return 0xff & (0xff - a);
}