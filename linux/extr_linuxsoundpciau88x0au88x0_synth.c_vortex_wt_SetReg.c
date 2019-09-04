#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mmio; TYPE_1__* card; } ;
typedef  TYPE_2__ vortex_t ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int NR_WT ; 
 int NR_WT_PB ; 
 int WT_ARAMP (int) ; 
 int WT_CTRL (int) ; 
 int WT_DELAY (int,int) ; 
 int WT_DSREG (int) ; 
 int WT_MRAMP (int) ; 
 int WT_MUTE (int) ; 
 int WT_PARM (int,int) ; 
 int WT_RUN (int) ; 
 int WT_SRAMP (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned char,int) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vortex_wt_SetReg(vortex_t * vortex, unsigned char reg, int wt,
		 u32 val)
{
	int ecx;

	if ((reg == 5) || ((reg >= 7) && (reg <= 10)) || (reg == 0xc)) {
		if (wt >= (NR_WT / NR_WT_PB)) {
			dev_warn(vortex->card->dev,
				 "WT SetReg: bank out of range. reg=0x%x, wt=%d\n",
				 reg, wt);
			return 0;
		}
	} else {
		if (wt >= NR_WT) {
			dev_err(vortex->card->dev,
				"WT SetReg: voice out of range\n");
			return 0;
		}
	}
	if (reg > 0xc)
		return 0;

	switch (reg) {
		/* Voice specific parameters */
	case 0:		/* running */
		/*
		pr_debug( "vortex: WT SetReg(0x%x) = 0x%08x\n",
		       WT_RUN(wt), (int)val);
		*/
		hwwrite(vortex->mmio, WT_RUN(wt), val);
		return 0xc;
	case 1:		/* param 0 */
		/*
		pr_debug( "vortex: WT SetReg(0x%x) = 0x%08x\n",
		       WT_PARM(wt,0), (int)val);
		*/
		hwwrite(vortex->mmio, WT_PARM(wt, 0), val);
		return 0xc;
	case 2:		/* param 1 */
		/*
		pr_debug( "vortex: WT SetReg(0x%x) = 0x%08x\n",
		       WT_PARM(wt,1), (int)val);
		*/
		hwwrite(vortex->mmio, WT_PARM(wt, 1), val);
		return 0xc;
	case 3:		/* param 2 */
		/*
		pr_debug( "vortex: WT SetReg(0x%x) = 0x%08x\n",
		       WT_PARM(wt,2), (int)val);
		*/
		hwwrite(vortex->mmio, WT_PARM(wt, 2), val);
		return 0xc;
	case 4:		/* param 3 */
		/*
		pr_debug( "vortex: WT SetReg(0x%x) = 0x%08x\n",
		       WT_PARM(wt,3), (int)val);
		*/
		hwwrite(vortex->mmio, WT_PARM(wt, 3), val);
		return 0xc;
	case 6:		/* mute */
		/*
		pr_debug( "vortex: WT SetReg(0x%x) = 0x%08x\n",
		       WT_MUTE(wt), (int)val);
		*/
		hwwrite(vortex->mmio, WT_MUTE(wt), val);
		return 0xc;
	case 0xb:
			/* delay */
		/*
		pr_debug( "vortex: WT SetReg(0x%x) = 0x%08x\n",
		       WT_DELAY(wt,0), (int)val);
		*/
		hwwrite(vortex->mmio, WT_DELAY(wt, 3), val);
		hwwrite(vortex->mmio, WT_DELAY(wt, 2), val);
		hwwrite(vortex->mmio, WT_DELAY(wt, 1), val);
		hwwrite(vortex->mmio, WT_DELAY(wt, 0), val);
		return 0xc;
		/* Global WT block parameters */
	case 5:		/* sramp */
		ecx = WT_SRAMP(wt);
		break;
	case 8:		/* aramp */
		ecx = WT_ARAMP(wt);
		break;
	case 9:		/* mramp */
		ecx = WT_MRAMP(wt);
		break;
	case 0xa:		/* ctrl */
		ecx = WT_CTRL(wt);
		break;
	case 0xc:		/* ds_reg */
		ecx = WT_DSREG(wt);
		break;
	default:
		return 0;
	}
	/*
	pr_debug( "vortex: WT SetReg(0x%x) = 0x%08x\n", ecx, (int)val);
	*/
	hwwrite(vortex->mmio, ecx, val);
	return 1;
}