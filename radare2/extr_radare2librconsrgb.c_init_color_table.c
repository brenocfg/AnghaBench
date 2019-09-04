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
 int* value_range ; 

__attribute__((used)) static void init_color_table() {
	int i, r, g, b;
	// ansi colors
	color_table[0] = 0x000000;
	color_table[1] = 0x800000;
	color_table[2] = 0x008000;
	color_table[3] = 0x808000;
	color_table[4] = 0x000080;
	color_table[5] = 0x800080;
	color_table[6] = 0x008080;
	color_table[7] = 0xc0c0c0;
	color_table[8] = 0x808080;
	color_table[9] = 0xff0000;
	color_table[10] = 0x00ff00;
	color_table[11] = 0xffff00;
	color_table[12] = 0x0000ff;
	color_table[13] = 0xff00ff;
	color_table[14] = 0x00ffff;
	color_table[15] = 0xffffff;
	// color palette
	for (i = 0; i < 216; i++) {
		r = value_range[(i / 36) % 6];
		g = value_range[(i / 6) % 6];
		b = value_range[i % 6];
		color_table[i + 16] = ((r << 16) & 0xffffff) +
			((g << 8) & 0xffff) + (b & 0xff);
	}
	// grayscale
	for (i = 0; i < 24; i++) {
		r = 8 + (i * 10);
		color_table[i + 232] = ((r << 16) & 0xffffff) +
			((r << 8) & 0xffff) + (r & 0xff);
	}
}