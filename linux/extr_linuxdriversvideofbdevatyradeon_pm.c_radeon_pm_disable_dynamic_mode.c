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
typedef  int u32 ;
struct radeonfb_info {scalar_t__ family; scalar_t__ is_mobility; scalar_t__ is_IGP; scalar_t__ has_CRTC2; } ;

/* Variables and functions */
 scalar_t__ CHIP_FAMILY_R300 ; 
 scalar_t__ CHIP_FAMILY_R350 ; 
 scalar_t__ CHIP_FAMILY_RV100 ; 
 scalar_t__ CHIP_FAMILY_RV350 ; 
 int CLK_PIN_CNTL__SCLK_DYN_START_CNTL ; 
 int INPLL (int /*<<< orphan*/ ) ; 
 int MCLK_CNTL__FORCE_AIC ; 
 int MCLK_CNTL__FORCE_MC ; 
 int MCLK_CNTL__FORCE_MCLKA ; 
 int MCLK_CNTL__FORCE_MCLKB ; 
 int MCLK_CNTL__FORCE_YCLKA ; 
 int MCLK_CNTL__FORCE_YCLKB ; 
 int MCLK_MISC__IO_MCLK_DYN_ENABLE ; 
 int MCLK_MISC__IO_MCLK_MAX_DYN_STOP_LAT ; 
 int MCLK_MISC__MC_MCLK_DYN_ENABLE ; 
 int MCLK_MISC__MC_MCLK_MAX_DYN_STOP_LAT ; 
 int /*<<< orphan*/  OUTPLL (int /*<<< orphan*/ ,int) ; 
 int PIXCLKS_CNTL__DISP_TVOUT_PIXCLK_TV_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__PIX2CLK_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__PIX2CLK_DAC_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__PIXCLK_BLEND_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__PIXCLK_DIG_TMDS_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__PIXCLK_GV_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__PIXCLK_LVDS_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__PIXCLK_TMDS_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__R300_DISP_DAC_PIXCLK_DAC2_BLANK_OFF ; 
 int PIXCLKS_CNTL__R300_DVOCLK_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__R300_P2G2CLK_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__R300_PIXCLK_DVO_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__R300_PIXCLK_TRANS_ALWAYS_ONb ; 
 int PIXCLKS_CNTL__R300_PIXCLK_TVO_ALWAYS_ONb ; 
 int SCLK_CNTL2__R300_FORCE_CBA ; 
 int SCLK_CNTL2__R300_FORCE_GA ; 
 int SCLK_CNTL2__R300_FORCE_TCL ; 
 int SCLK_CNTL__CP_MAX_DYN_STOP_LAT ; 
 int SCLK_CNTL__DYN_STOP_LAT_MASK ; 
 int SCLK_CNTL__FORCEON_MASK ; 
 int SCLK_CNTL__FORCE_CP ; 
 int SCLK_CNTL__FORCE_DISP1 ; 
 int SCLK_CNTL__FORCE_DISP2 ; 
 int SCLK_CNTL__FORCE_E2 ; 
 int SCLK_CNTL__FORCE_HDP ; 
 int SCLK_CNTL__FORCE_IDCT ; 
 int SCLK_CNTL__FORCE_OV0 ; 
 int SCLK_CNTL__FORCE_PB ; 
 int SCLK_CNTL__FORCE_RB ; 
 int SCLK_CNTL__FORCE_RE ; 
 int SCLK_CNTL__FORCE_SE ; 
 int SCLK_CNTL__FORCE_SUBPIC ; 
 int SCLK_CNTL__FORCE_TAM ; 
 int SCLK_CNTL__FORCE_TDM ; 
 int SCLK_CNTL__FORCE_TOP ; 
 int SCLK_CNTL__FORCE_TV_SCLK ; 
 int SCLK_CNTL__FORCE_VIP ; 
 int SCLK_CNTL__R300_FORCE_PX ; 
 int SCLK_CNTL__R300_FORCE_SR ; 
 int SCLK_CNTL__R300_FORCE_SU ; 
 int SCLK_CNTL__R300_FORCE_TX ; 
 int SCLK_CNTL__R300_FORCE_US ; 
 int SCLK_CNTL__R300_FORCE_VAP ; 
 int SCLK_MORE_CNTL__FORCE_DISPREGS ; 
 int SCLK_MORE_CNTL__FORCE_MC_GUI ; 
 int SCLK_MORE_CNTL__FORCE_MC_HOST ; 
 int VCLK_ECP_CNTL__PIXCLK_ALWAYS_ONb ; 
 int VCLK_ECP_CNTL__PIXCLK_DAC_ALWAYS_ONb ; 
 int VCLK_ECP_CNTL__R300_DISP_DAC_PIXCLK_DAC_BLANK_OFF ; 
 int /*<<< orphan*/  pllCLK_PIN_CNTL ; 
 int /*<<< orphan*/  pllMCLK_CNTL ; 
 int /*<<< orphan*/  pllMCLK_MISC ; 
 int /*<<< orphan*/  pllPIXCLKS_CNTL ; 
 int /*<<< orphan*/  pllSCLK_CNTL ; 
 int /*<<< orphan*/  pllSCLK_CNTL2 ; 
 int /*<<< orphan*/  pllSCLK_MORE_CNTL ; 
 int /*<<< orphan*/  pllVCLK_ECP_CNTL ; 
 int /*<<< orphan*/  radeon_msleep (int) ; 

__attribute__((used)) static void radeon_pm_disable_dynamic_mode(struct radeonfb_info *rinfo)
{
	u32 tmp;

	/* RV100 */
	if ((rinfo->family == CHIP_FAMILY_RV100) && (!rinfo->is_mobility)) {
		if (rinfo->has_CRTC2) {
			tmp = INPLL(pllSCLK_CNTL);
			tmp &= ~SCLK_CNTL__DYN_STOP_LAT_MASK;
			tmp |= SCLK_CNTL__CP_MAX_DYN_STOP_LAT | SCLK_CNTL__FORCEON_MASK;
			OUTPLL(pllSCLK_CNTL, tmp);
		}
		tmp = INPLL(pllMCLK_CNTL);
		tmp |= (MCLK_CNTL__FORCE_MCLKA |
		        MCLK_CNTL__FORCE_MCLKB |
		        MCLK_CNTL__FORCE_YCLKA |
		        MCLK_CNTL__FORCE_YCLKB |
			MCLK_CNTL__FORCE_AIC |
			MCLK_CNTL__FORCE_MC);
                OUTPLL(pllMCLK_CNTL, tmp);
		return;
	}
	/* R100 */
	if (!rinfo->has_CRTC2) {
                tmp = INPLL(pllSCLK_CNTL);
                tmp |= (SCLK_CNTL__FORCE_CP	| SCLK_CNTL__FORCE_HDP	|
			SCLK_CNTL__FORCE_DISP1	| SCLK_CNTL__FORCE_TOP	|
                        SCLK_CNTL__FORCE_E2	| SCLK_CNTL__FORCE_SE 	|
			SCLK_CNTL__FORCE_IDCT	| SCLK_CNTL__FORCE_VIP	|
			SCLK_CNTL__FORCE_RE	| SCLK_CNTL__FORCE_PB 	|
			SCLK_CNTL__FORCE_TAM	| SCLK_CNTL__FORCE_TDM	|
                        SCLK_CNTL__FORCE_RB);
                OUTPLL(pllSCLK_CNTL, tmp);
		return;
	}
	/* RV350 (M10/M11) */
	if (rinfo->family == CHIP_FAMILY_RV350) {
                /* for RV350/M10/M11, no delays are required. */
                tmp = INPLL(pllSCLK_CNTL2);
                tmp |= (SCLK_CNTL2__R300_FORCE_TCL |
                        SCLK_CNTL2__R300_FORCE_GA  |
			SCLK_CNTL2__R300_FORCE_CBA);
                OUTPLL(pllSCLK_CNTL2, tmp);

                tmp = INPLL(pllSCLK_CNTL);
                tmp |= (SCLK_CNTL__FORCE_DISP2		| SCLK_CNTL__FORCE_CP		|
                        SCLK_CNTL__FORCE_HDP		| SCLK_CNTL__FORCE_DISP1	|
                        SCLK_CNTL__FORCE_TOP		| SCLK_CNTL__FORCE_E2		|
                        SCLK_CNTL__R300_FORCE_VAP	| SCLK_CNTL__FORCE_IDCT    	|
			SCLK_CNTL__FORCE_VIP		| SCLK_CNTL__R300_FORCE_SR	|
			SCLK_CNTL__R300_FORCE_PX	| SCLK_CNTL__R300_FORCE_TX	|
			SCLK_CNTL__R300_FORCE_US	| SCLK_CNTL__FORCE_TV_SCLK	|
                        SCLK_CNTL__R300_FORCE_SU	| SCLK_CNTL__FORCE_OV0);
                OUTPLL(pllSCLK_CNTL, tmp);

                tmp = INPLL(pllSCLK_MORE_CNTL);
		tmp |= (SCLK_MORE_CNTL__FORCE_DISPREGS	| SCLK_MORE_CNTL__FORCE_MC_GUI	|
			SCLK_MORE_CNTL__FORCE_MC_HOST);
                OUTPLL(pllSCLK_MORE_CNTL, tmp);

		tmp = INPLL(pllMCLK_CNTL);
		tmp |= (MCLK_CNTL__FORCE_MCLKA |
		        MCLK_CNTL__FORCE_MCLKB |
		        MCLK_CNTL__FORCE_YCLKA |
		        MCLK_CNTL__FORCE_YCLKB |
			MCLK_CNTL__FORCE_MC);
                OUTPLL(pllMCLK_CNTL, tmp);

                tmp = INPLL(pllVCLK_ECP_CNTL);
                tmp &= ~(VCLK_ECP_CNTL__PIXCLK_ALWAYS_ONb  |
                         VCLK_ECP_CNTL__PIXCLK_DAC_ALWAYS_ONb |
			 VCLK_ECP_CNTL__R300_DISP_DAC_PIXCLK_DAC_BLANK_OFF);
                OUTPLL(pllVCLK_ECP_CNTL, tmp);

                tmp = INPLL(pllPIXCLKS_CNTL);
                tmp &= ~(PIXCLKS_CNTL__PIX2CLK_ALWAYS_ONb		|
			 PIXCLKS_CNTL__PIX2CLK_DAC_ALWAYS_ONb		|
			 PIXCLKS_CNTL__DISP_TVOUT_PIXCLK_TV_ALWAYS_ONb	|
			 PIXCLKS_CNTL__R300_DVOCLK_ALWAYS_ONb		|
			 PIXCLKS_CNTL__PIXCLK_BLEND_ALWAYS_ONb		|
			 PIXCLKS_CNTL__PIXCLK_GV_ALWAYS_ONb		|
			 PIXCLKS_CNTL__R300_PIXCLK_DVO_ALWAYS_ONb	|
			 PIXCLKS_CNTL__PIXCLK_LVDS_ALWAYS_ONb		|
			 PIXCLKS_CNTL__PIXCLK_TMDS_ALWAYS_ONb		|
			 PIXCLKS_CNTL__R300_PIXCLK_TRANS_ALWAYS_ONb	|
			 PIXCLKS_CNTL__R300_PIXCLK_TVO_ALWAYS_ONb	|
			 PIXCLKS_CNTL__R300_P2G2CLK_ALWAYS_ONb		|
			 PIXCLKS_CNTL__R300_DISP_DAC_PIXCLK_DAC2_BLANK_OFF);
                OUTPLL(pllPIXCLKS_CNTL, tmp);

		return;
	}
	
	/* Default */

	/* Force Core Clocks */
	tmp = INPLL(pllSCLK_CNTL);
	tmp |= (SCLK_CNTL__FORCE_CP | SCLK_CNTL__FORCE_E2);

	/* XFree doesn't do that case, but we had this code from Apple and it
	 * seem necessary for proper suspend/resume operations
	 */
	if (rinfo->is_mobility) {
		tmp |= 	SCLK_CNTL__FORCE_HDP|
			SCLK_CNTL__FORCE_DISP1|
			SCLK_CNTL__FORCE_DISP2|
			SCLK_CNTL__FORCE_TOP|
			SCLK_CNTL__FORCE_SE|
			SCLK_CNTL__FORCE_IDCT|
			SCLK_CNTL__FORCE_VIP|
			SCLK_CNTL__FORCE_PB|
			SCLK_CNTL__FORCE_RE|
			SCLK_CNTL__FORCE_TAM|
			SCLK_CNTL__FORCE_TDM|
			SCLK_CNTL__FORCE_RB|
			SCLK_CNTL__FORCE_TV_SCLK|
			SCLK_CNTL__FORCE_SUBPIC|
			SCLK_CNTL__FORCE_OV0;
	}
	else if (rinfo->family == CHIP_FAMILY_R300 ||
		   rinfo->family == CHIP_FAMILY_R350) {
		tmp |=  SCLK_CNTL__FORCE_HDP   |
			SCLK_CNTL__FORCE_DISP1 |
			SCLK_CNTL__FORCE_DISP2 |
			SCLK_CNTL__FORCE_TOP   |
			SCLK_CNTL__FORCE_IDCT  |
			SCLK_CNTL__FORCE_VIP;
	}
    	OUTPLL(pllSCLK_CNTL, tmp);
	radeon_msleep(16);

	if (rinfo->family == CHIP_FAMILY_R300 || rinfo->family == CHIP_FAMILY_R350) {
		tmp = INPLL(pllSCLK_CNTL2);
		tmp |=  SCLK_CNTL2__R300_FORCE_TCL |
			SCLK_CNTL2__R300_FORCE_GA  |
			SCLK_CNTL2__R300_FORCE_CBA;
		OUTPLL(pllSCLK_CNTL2, tmp);
		radeon_msleep(16);
	}

	tmp = INPLL(pllCLK_PIN_CNTL);
	tmp &= ~CLK_PIN_CNTL__SCLK_DYN_START_CNTL;
	OUTPLL(pllCLK_PIN_CNTL, tmp);
	radeon_msleep(15);

	if (rinfo->is_IGP) {
		/* Weird  ... X is _un_ forcing clocks here, I think it's
		 * doing backward. Imitate it for now...
		 */
		tmp = INPLL(pllMCLK_CNTL);
		tmp &= ~(MCLK_CNTL__FORCE_MCLKA |
			 MCLK_CNTL__FORCE_YCLKA);
		OUTPLL(pllMCLK_CNTL, tmp);
		radeon_msleep(16);
	}
	/* Hrm... same shit, X doesn't do that but I have to */
	else if (rinfo->is_mobility) {
		tmp = INPLL(pllMCLK_CNTL);
		tmp |= (MCLK_CNTL__FORCE_MCLKA |
			MCLK_CNTL__FORCE_MCLKB |
			MCLK_CNTL__FORCE_YCLKA |
			MCLK_CNTL__FORCE_YCLKB);
		OUTPLL(pllMCLK_CNTL, tmp);
		radeon_msleep(16);

		tmp = INPLL(pllMCLK_MISC);
		tmp &= 	~(MCLK_MISC__MC_MCLK_MAX_DYN_STOP_LAT|
			  MCLK_MISC__IO_MCLK_MAX_DYN_STOP_LAT|
			  MCLK_MISC__MC_MCLK_DYN_ENABLE|
			  MCLK_MISC__IO_MCLK_DYN_ENABLE);
		OUTPLL(pllMCLK_MISC, tmp);
		radeon_msleep(15);
	}

	if (rinfo->is_mobility) {
		tmp = INPLL(pllSCLK_MORE_CNTL);
		tmp |= 	SCLK_MORE_CNTL__FORCE_DISPREGS|
			SCLK_MORE_CNTL__FORCE_MC_GUI|
			SCLK_MORE_CNTL__FORCE_MC_HOST;
		OUTPLL(pllSCLK_MORE_CNTL, tmp);
		radeon_msleep(16);
	}

	tmp = INPLL(pllPIXCLKS_CNTL);
	tmp &= ~(PIXCLKS_CNTL__PIXCLK_GV_ALWAYS_ONb |
		 PIXCLKS_CNTL__PIXCLK_BLEND_ALWAYS_ONb|
		 PIXCLKS_CNTL__PIXCLK_DIG_TMDS_ALWAYS_ONb |
		 PIXCLKS_CNTL__PIXCLK_LVDS_ALWAYS_ONb|
		 PIXCLKS_CNTL__PIXCLK_TMDS_ALWAYS_ONb|
		 PIXCLKS_CNTL__PIX2CLK_ALWAYS_ONb|
		 PIXCLKS_CNTL__PIX2CLK_DAC_ALWAYS_ONb);
 	OUTPLL(pllPIXCLKS_CNTL, tmp);
	radeon_msleep(16);

	tmp = INPLL( pllVCLK_ECP_CNTL);
	tmp &= ~(VCLK_ECP_CNTL__PIXCLK_ALWAYS_ONb |
		 VCLK_ECP_CNTL__PIXCLK_DAC_ALWAYS_ONb);
	OUTPLL( pllVCLK_ECP_CNTL, tmp);
	radeon_msleep(16);
}