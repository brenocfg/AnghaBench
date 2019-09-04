#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int height; int width; } ;
struct vc_data {TYPE_1__ vc_font; } ;

/* Variables and functions */
 int FBCON_ATTRIBUTE_BOLD ; 
 int FBCON_ATTRIBUTE_REVERSE ; 
 int FBCON_ATTRIBUTE_UNDERLINE ; 

__attribute__((used)) static void ccw_update_attr(u8 *dst, u8 *src, int attribute,
				  struct vc_data *vc)
{
	int i, j, offset = (vc->vc_font.height < 10) ? 1 : 2;
	int width = (vc->vc_font.height + 7) >> 3;
	int mod = vc->vc_font.height % 8;
	u8 c, msk = ~(0xff << offset), msk1 = 0;

	if (mod)
		msk <<= (8 - mod);

	if (offset > mod)
		msk1 |= 0x01;

	for (i = 0; i < vc->vc_font.width; i++) {
		for (j = 0; j < width; j++) {
			c = *src;

			if (attribute & FBCON_ATTRIBUTE_UNDERLINE) {
				if (j == width - 1)
					c |= msk;

				if (msk1 && j == width - 2)
					c |= msk1;
			}

			if (attribute & FBCON_ATTRIBUTE_BOLD && i)
				*(dst - width) |= c;

			if (attribute & FBCON_ATTRIBUTE_REVERSE)
				c = ~c;
			src++;
			*dst++ = c;
		}
	}
}