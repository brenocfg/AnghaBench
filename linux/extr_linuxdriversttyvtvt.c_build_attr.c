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
struct vc_data {int vc_itcolor; int vc_ulcolor; int vc_halfcolor; int vc_hi_font_mask; int /*<<< orphan*/  vc_can_do_color; TYPE_1__* vc_sw; } ;
typedef  int a ;
struct TYPE_2__ {int (* con_build_attr ) (struct vc_data*,int,int,int,int,int,int) ;} ;

/* Variables and functions */
 int stub1 (struct vc_data*,int,int,int,int,int,int) ; 

__attribute__((used)) static u8 build_attr(struct vc_data *vc, u8 _color, u8 _intensity, u8 _blink,
    u8 _underline, u8 _reverse, u8 _italic)
{
	if (vc->vc_sw->con_build_attr)
		return vc->vc_sw->con_build_attr(vc, _color, _intensity,
		       _blink, _underline, _reverse, _italic);

/*
 * ++roman: I completely changed the attribute format for monochrome
 * mode (!can_do_color). The formerly used MDA (monochrome display
 * adapter) format didn't allow the combination of certain effects.
 * Now the attribute is just a bit vector:
 *  Bit 0..1: intensity (0..2)
 *  Bit 2   : underline
 *  Bit 3   : reverse
 *  Bit 7   : blink
 */
	{
	u8 a = _color;
	if (!vc->vc_can_do_color)
		return _intensity |
		       (_italic ? 2 : 0) |
		       (_underline ? 4 : 0) |
		       (_reverse ? 8 : 0) |
		       (_blink ? 0x80 : 0);
	if (_italic)
		a = (a & 0xF0) | vc->vc_itcolor;
	else if (_underline)
		a = (a & 0xf0) | vc->vc_ulcolor;
	else if (_intensity == 0)
		a = (a & 0xf0) | vc->vc_halfcolor;
	if (_reverse)
		a = ((a) & 0x88) | ((((a) >> 4) | ((a) << 4)) & 0x77);
	if (_blink)
		a ^= 0x80;
	if (_intensity == 2)
		a ^= 0x08;
	if (vc->vc_hi_font_mask == 0x100)
		a <<= 1;
	return a;
	}
}