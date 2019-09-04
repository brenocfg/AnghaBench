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
struct pm3_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm3fb_set_color (struct pm3_par*,int,unsigned char,unsigned char,unsigned char) ; 

__attribute__((used)) static void pm3fb_clear_colormap(struct pm3_par *par,
			unsigned char r, unsigned char g, unsigned char b)
{
	int i;

	for (i = 0; i < 256 ; i++)
		pm3fb_set_color(par, i, r, g, b);

}