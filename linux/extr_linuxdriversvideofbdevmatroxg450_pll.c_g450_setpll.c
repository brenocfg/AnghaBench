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
struct matrox_fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC1064_XSYSPLLM ; 
 int /*<<< orphan*/  DAC1064_XSYSPLLN ; 
 int /*<<< orphan*/  DAC1064_XSYSPLLP ; 
 unsigned int DAC1064_XSYSPLLSTAT ; 
 int /*<<< orphan*/  M1064_XPIXPLLAM ; 
 int /*<<< orphan*/  M1064_XPIXPLLAN ; 
 int /*<<< orphan*/  M1064_XPIXPLLAP ; 
 int /*<<< orphan*/  M1064_XPIXPLLBM ; 
 int /*<<< orphan*/  M1064_XPIXPLLBN ; 
 int /*<<< orphan*/  M1064_XPIXPLLBP ; 
 int /*<<< orphan*/  M1064_XPIXPLLCM ; 
 int /*<<< orphan*/  M1064_XPIXPLLCN ; 
 int /*<<< orphan*/  M1064_XPIXPLLCP ; 
 unsigned int M1064_XPIXPLLSTAT ; 
 int /*<<< orphan*/  M1064_XVIDPLLM ; 
 int /*<<< orphan*/  M1064_XVIDPLLN ; 
 int /*<<< orphan*/  M1064_XVIDPLLP ; 
 unsigned int M1064_XVIDPLLSTAT ; 
#define  M_PIXEL_PLL_A 132 
#define  M_PIXEL_PLL_B 131 
#define  M_PIXEL_PLL_C 130 
#define  M_SYSTEM_PLL 129 
#define  M_VIDEO_PLL 128 
 int /*<<< orphan*/  matroxfb_DAC_out (struct matrox_fb_info const*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline unsigned int g450_setpll(const struct matrox_fb_info *minfo,
				       unsigned int mnp, unsigned int pll)
{
	switch (pll) {
		case M_PIXEL_PLL_A:
			matroxfb_DAC_out(minfo, M1064_XPIXPLLAM, mnp >> 16);
			matroxfb_DAC_out(minfo, M1064_XPIXPLLAN, mnp >> 8);
			matroxfb_DAC_out(minfo, M1064_XPIXPLLAP, mnp);
			return M1064_XPIXPLLSTAT;

		case M_PIXEL_PLL_B:
			matroxfb_DAC_out(minfo, M1064_XPIXPLLBM, mnp >> 16);
			matroxfb_DAC_out(minfo, M1064_XPIXPLLBN, mnp >> 8);
			matroxfb_DAC_out(minfo, M1064_XPIXPLLBP, mnp);
			return M1064_XPIXPLLSTAT;

		case M_PIXEL_PLL_C:
			matroxfb_DAC_out(minfo, M1064_XPIXPLLCM, mnp >> 16);
			matroxfb_DAC_out(minfo, M1064_XPIXPLLCN, mnp >> 8);
			matroxfb_DAC_out(minfo, M1064_XPIXPLLCP, mnp);
			return M1064_XPIXPLLSTAT;

		case M_SYSTEM_PLL:
			matroxfb_DAC_out(minfo, DAC1064_XSYSPLLM, mnp >> 16);
			matroxfb_DAC_out(minfo, DAC1064_XSYSPLLN, mnp >> 8);
			matroxfb_DAC_out(minfo, DAC1064_XSYSPLLP, mnp);
			return DAC1064_XSYSPLLSTAT;

		case M_VIDEO_PLL:
			matroxfb_DAC_out(minfo, M1064_XVIDPLLM, mnp >> 16);
			matroxfb_DAC_out(minfo, M1064_XVIDPLLN, mnp >> 8);
			matroxfb_DAC_out(minfo, M1064_XVIDPLLP, mnp);
			return M1064_XVIDPLLSTAT;
	}
	return 0;
}