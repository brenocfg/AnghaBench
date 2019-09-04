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
struct rgb {int r; int g; int b; } ;

/* Variables and functions */

__attribute__((used)) static void rgb_from_256(int i, struct rgb *c)
{
	if (i < 8) {            /* Standard colours. */
		c->r = i&1 ? 0xaa : 0x00;
		c->g = i&2 ? 0xaa : 0x00;
		c->b = i&4 ? 0xaa : 0x00;
	} else if (i < 16) {
		c->r = i&1 ? 0xff : 0x55;
		c->g = i&2 ? 0xff : 0x55;
		c->b = i&4 ? 0xff : 0x55;
	} else if (i < 232) {   /* 6x6x6 colour cube. */
		c->r = (i - 16) / 36 * 85 / 2;
		c->g = (i - 16) / 6 % 6 * 85 / 2;
		c->b = (i - 16) % 6 * 85 / 2;
	} else                  /* Grayscale ramp. */
		c->r = c->g = c->b = i * 10 - 2312;
}