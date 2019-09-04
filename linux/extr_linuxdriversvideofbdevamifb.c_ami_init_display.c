#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
struct amifb_par {int bplcon0; int beamcon0; int /*<<< orphan*/  htotal; int /*<<< orphan*/  fmode; scalar_t__ hsstop; int /*<<< orphan*/  vsstop; int /*<<< orphan*/  vsstrt; int /*<<< orphan*/  vbstop; int /*<<< orphan*/  vbstrt; int /*<<< orphan*/  vtotal; int /*<<< orphan*/  hcenter; int /*<<< orphan*/  hsstrt; int /*<<< orphan*/  hbstop; int /*<<< orphan*/  hbstrt; int /*<<< orphan*/  bplcon3; } ;
struct TYPE_4__ {int /*<<< orphan*/ ** list; } ;
struct TYPE_3__ {int bplcon0; int bplcon2; int bplcon4; int beamcon0; int vposr; int vposw; int /*<<< orphan*/ * cop2lc; int /*<<< orphan*/  fmode; int /*<<< orphan*/  vsstop; int /*<<< orphan*/  vsstrt; int /*<<< orphan*/  vbstop; int /*<<< orphan*/  vbstrt; int /*<<< orphan*/  vtotal; int /*<<< orphan*/  hcenter; int /*<<< orphan*/  hsstop; int /*<<< orphan*/  hsstrt; int /*<<< orphan*/  hbstop; int /*<<< orphan*/  hbstrt; int /*<<< orphan*/  htotal; int /*<<< orphan*/  bplcon3; } ;

/* Variables and functions */
 int BMC0_VARBEAMEN ; 
 int BPC0_LACE ; 
 int BPC2_KILLEHB ; 
 int BPC2_PF1P2 ; 
 int BPC2_PF2P2 ; 
 int BPC4_ESPRM4 ; 
 int BPC4_OSPRM4 ; 
 scalar_t__ IS_AGA ; 
 scalar_t__ IS_OCS ; 
 scalar_t__ ZTWO_PADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amiga_audio_min_period ; 
 TYPE_2__ copdisplay ; 
 size_t currentcop ; 
 TYPE_1__ custom ; 
 int /*<<< orphan*/  div16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hbstop2hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hbstrt2hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hcenter2hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsstop2hw (scalar_t__) ; 
 int /*<<< orphan*/  hsstrt2hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htotal2hw (int /*<<< orphan*/ ) ; 
 int is_lace ; 
 int /*<<< orphan*/  vbstop2hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbstrt2hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsstop2hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsstrt2hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtotal2hw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ami_init_display(const struct amifb_par *par)
{
	int i;

	custom.bplcon0 = par->bplcon0 & ~BPC0_LACE;
	custom.bplcon2 = (IS_OCS ? 0 : BPC2_KILLEHB) | BPC2_PF2P2 | BPC2_PF1P2;
	if (!IS_OCS) {
		custom.bplcon3 = par->bplcon3;
		if (IS_AGA)
			custom.bplcon4 = BPC4_ESPRM4 | BPC4_OSPRM4;
		if (par->beamcon0 & BMC0_VARBEAMEN) {
			custom.htotal = htotal2hw(par->htotal);
			custom.hbstrt = hbstrt2hw(par->hbstrt);
			custom.hbstop = hbstop2hw(par->hbstop);
			custom.hsstrt = hsstrt2hw(par->hsstrt);
			custom.hsstop = hsstop2hw(par->hsstop);
			custom.hcenter = hcenter2hw(par->hcenter);
			custom.vtotal = vtotal2hw(par->vtotal);
			custom.vbstrt = vbstrt2hw(par->vbstrt);
			custom.vbstop = vbstop2hw(par->vbstop);
			custom.vsstrt = vsstrt2hw(par->vsstrt);
			custom.vsstop = vsstop2hw(par->vsstop);
		}
	}
	if (!IS_OCS || par->hsstop)
		custom.beamcon0 = par->beamcon0;
	if (IS_AGA)
		custom.fmode = par->fmode;

	/*
	 * The minimum period for audio depends on htotal
	 */

	amiga_audio_min_period = div16(par->htotal);

	is_lace = par->bplcon0 & BPC0_LACE ? 1 : 0;
#if 1
	if (is_lace) {
		i = custom.vposr >> 15;
	} else {
		custom.vposw = custom.vposr | 0x8000;
		i = 1;
	}
#else
	i = 1;
	custom.vposw = custom.vposr | 0x8000;
#endif
	custom.cop2lc = (u_short *)ZTWO_PADDR(copdisplay.list[currentcop][i]);
}