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
 int /*<<< orphan*/  M1064_XPIXPLLAM ; 
 int /*<<< orphan*/  M1064_XPIXPLLAN ; 
 int /*<<< orphan*/  M1064_XPIXPLLAP ; 
 int /*<<< orphan*/  M1064_XPIXPLLBM ; 
 int /*<<< orphan*/  M1064_XPIXPLLBN ; 
 int /*<<< orphan*/  M1064_XPIXPLLBP ; 
 int /*<<< orphan*/  M1064_XPIXPLLCM ; 
 int /*<<< orphan*/  M1064_XPIXPLLCN ; 
 int /*<<< orphan*/  M1064_XPIXPLLCP ; 
 int /*<<< orphan*/  M1064_XVIDPLLM ; 
 int /*<<< orphan*/  M1064_XVIDPLLN ; 
 int /*<<< orphan*/  M1064_XVIDPLLP ; 
#define  M_PIXEL_PLL_A 132 
#define  M_PIXEL_PLL_B 131 
#define  M_PIXEL_PLL_C 130 
#define  M_SYSTEM_PLL 129 
#define  M_VIDEO_PLL 128 
 unsigned char matroxfb_DAC_in (struct matrox_fb_info const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int g450_cmppll(const struct matrox_fb_info *minfo,
				       unsigned int mnp, unsigned int pll)
{
	unsigned char m = mnp >> 16;
	unsigned char n = mnp >> 8;
	unsigned char p = mnp;

	switch (pll) {
		case M_PIXEL_PLL_A:
			return (matroxfb_DAC_in(minfo, M1064_XPIXPLLAM) != m ||
				matroxfb_DAC_in(minfo, M1064_XPIXPLLAN) != n ||
				matroxfb_DAC_in(minfo, M1064_XPIXPLLAP) != p);

		case M_PIXEL_PLL_B:
			return (matroxfb_DAC_in(minfo, M1064_XPIXPLLBM) != m ||
				matroxfb_DAC_in(minfo, M1064_XPIXPLLBN) != n ||
				matroxfb_DAC_in(minfo, M1064_XPIXPLLBP) != p);

		case M_PIXEL_PLL_C:
			return (matroxfb_DAC_in(minfo, M1064_XPIXPLLCM) != m ||
				matroxfb_DAC_in(minfo, M1064_XPIXPLLCN) != n ||
				matroxfb_DAC_in(minfo, M1064_XPIXPLLCP) != p);

		case M_SYSTEM_PLL:
			return (matroxfb_DAC_in(minfo, DAC1064_XSYSPLLM) != m ||
				matroxfb_DAC_in(minfo, DAC1064_XSYSPLLN) != n ||
				matroxfb_DAC_in(minfo, DAC1064_XSYSPLLP) != p);

		case M_VIDEO_PLL:
			return (matroxfb_DAC_in(minfo, M1064_XVIDPLLM) != m ||
				matroxfb_DAC_in(minfo, M1064_XVIDPLLN) != n ||
				matroxfb_DAC_in(minfo, M1064_XVIDPLLP) != p);
	}
	return 1;
}