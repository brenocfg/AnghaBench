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
typedef  int ut8 ;
typedef  int /*<<< orphan*/  (* PrintfCallback ) (char*,int,int) ;

/* Variables and functions */

__attribute__((used)) static void render_greyscale(PrintfCallback cb_printf, const ut8 *c, const ut8 *d) {
	int color1, color2, k;
	color1 = (c[0]+c[1]+c[2]) / 3;
	color2 = (d[0]+d[1]+d[2]) / 3;
	k = 231 + ((int)((float)color1/10.3));
	if (k<232) k = 232;
	cb_printf ("\x1b[%d;5;%dm", 48, k); // bg
	k = 231 + ((int)((float)color2/10.3));
	if (k<232) k = 232;
	cb_printf ("\x1b[%d;5;%dm", 38, k); // fg
}