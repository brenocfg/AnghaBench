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
 int* color_table ; 

__attribute__((used)) static int lookup_rgb(int r, int g, int b) {
	int i, color = (r << 16) + (g << 8) + b;
	// lookup extended colors only, coz non-extended can be changed by users.
	for (i = 16; i < 256; ++i) {
		if (color_table[i] == color) {
			return i;
		}
	}
	return -1;
}