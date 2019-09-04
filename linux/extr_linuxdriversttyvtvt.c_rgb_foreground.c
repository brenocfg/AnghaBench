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
typedef  int u8 ;
struct vc_data {int vc_intensity; int vc_color; } ;
struct rgb {int r; int g; int b; } ;

/* Variables and functions */
 int max3 (int,int,int) ; 

__attribute__((used)) static void rgb_foreground(struct vc_data *vc, const struct rgb *c)
{
	u8 hue = 0, max = max3(c->r, c->g, c->b);

	if (c->r > max / 2)
		hue |= 4;
	if (c->g > max / 2)
		hue |= 2;
	if (c->b > max / 2)
		hue |= 1;

	if (hue == 7 && max <= 0x55) {
		hue = 0;
		vc->vc_intensity = 2;
	} else if (max > 0xaa)
		vc->vc_intensity = 2;
	else
		vc->vc_intensity = 1;

	vc->vc_color = (vc->vc_color & 0xf0) | hue;
}