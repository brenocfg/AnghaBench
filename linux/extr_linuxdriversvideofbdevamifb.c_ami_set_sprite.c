#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_short ;
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_4__ {short crsr_x; short spot_x; short crsr_y; short spot_y; int height; int fmode; scalar_t__ width; } ;
struct amifb_par {int vmode; short xres; short yres; short clk_shift; short line_shift; int bplcon0; int fmode; TYPE_1__ crsr; scalar_t__ diwstrt_v; scalar_t__ diwstrt_h; scalar_t__ yoffset; scalar_t__ xoffset; } ;
struct TYPE_5__ {void** w; } ;
typedef  TYPE_2__ copins ;
struct TYPE_6__ {TYPE_2__*** list; } ;

/* Variables and functions */
 int BPC0_LACE ; 
 int FB_VMODE_YWRAP ; 
 int FMODE_BSCAN2 ; 
 scalar_t__ IS_AGA ; 
 int /*<<< orphan*/  ZTWO_PADDR (int*) ; 
 size_t cop_spr0ptrh ; 
 size_t cop_spr0ptrl ; 
 TYPE_3__ copdisplay ; 
 size_t currentcop ; 
 scalar_t__ cursorstate ; 
 int* dummysprite ; 
 void* highw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_blanked ; 
 int* lofsprite ; 
 void* loww (int /*<<< orphan*/ ) ; 
 scalar_t__ mod2 (scalar_t__) ; 
 int* shfsprite ; 
 int spr2hw_ctl (scalar_t__,scalar_t__,scalar_t__) ; 
 int spr2hw_pos (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ami_set_sprite(const struct amifb_par *par)
{
	copins *copl, *cops;
	u_short hs, vs, ve;
	u_long pl, ps;
	short mx, my;

	cops = copdisplay.list[currentcop][0];
	copl = copdisplay.list[currentcop][1];
	ps = pl = ZTWO_PADDR(dummysprite);
	mx = par->crsr.crsr_x - par->crsr.spot_x;
	my = par->crsr.crsr_y - par->crsr.spot_y;
	if (!(par->vmode & FB_VMODE_YWRAP)) {
		mx -= par->xoffset;
		my -= par->yoffset;
	}
	if (!is_blanked && cursorstate > 0 && par->crsr.height > 0 &&
	    mx > -(short)par->crsr.width && mx < par->xres &&
	    my > -(short)par->crsr.height && my < par->yres) {
		pl = ZTWO_PADDR(lofsprite);
		hs = par->diwstrt_h + (mx << par->clk_shift) - 4;
		vs = par->diwstrt_v + (my << par->line_shift);
		ve = vs + (par->crsr.height << par->line_shift);
		if (par->bplcon0 & BPC0_LACE) {
			ps = ZTWO_PADDR(shfsprite);
			lofsprite[0] = spr2hw_pos(vs, hs);
			shfsprite[0] = spr2hw_pos(vs + 1, hs);
			if (mod2(vs)) {
				lofsprite[1 << par->crsr.fmode] = spr2hw_ctl(vs, hs, ve);
				shfsprite[1 << par->crsr.fmode] = spr2hw_ctl(vs + 1, hs, ve + 1);
				swap(pl, ps);
			} else {
				lofsprite[1 << par->crsr.fmode] = spr2hw_ctl(vs, hs, ve + 1);
				shfsprite[1 << par->crsr.fmode] = spr2hw_ctl(vs + 1, hs, ve);
			}
		} else {
			lofsprite[0] = spr2hw_pos(vs, hs) | (IS_AGA && (par->fmode & FMODE_BSCAN2) ? 0x80 : 0);
			lofsprite[1 << par->crsr.fmode] = spr2hw_ctl(vs, hs, ve);
		}
	}
	copl[cop_spr0ptrh].w[1] = highw(pl);
	copl[cop_spr0ptrl].w[1] = loww(pl);
	if (par->bplcon0 & BPC0_LACE) {
		cops[cop_spr0ptrh].w[1] = highw(ps);
		cops[cop_spr0ptrl].w[1] = loww(ps);
	}
}