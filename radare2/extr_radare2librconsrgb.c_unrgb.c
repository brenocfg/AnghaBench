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

__attribute__((used)) static void unrgb(int color, int *r, int *g, int *b) {
	if (color < 0 || color > 256) {
		*r = *g = *b = 0;
		return;
	}
	int rgb = color_table[color];
	*r = (rgb >> 16) & 0xff;
	*g = (rgb >> 8) & 0xff;
	*b = rgb & 0xff;
}