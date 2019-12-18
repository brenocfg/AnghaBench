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
struct device {int dummy; } ;

/* Variables and functions */
 int BYT_RT5651_DMIC_EN ; 
 scalar_t__ BYT_RT5651_DMIC_MAP ; 
 scalar_t__ BYT_RT5651_IN1_IN2_MAP ; 
 scalar_t__ BYT_RT5651_IN1_MAP ; 
 scalar_t__ BYT_RT5651_IN2_MAP ; 
 scalar_t__ BYT_RT5651_JDSRC (int) ; 
 int BYT_RT5651_JD_NOT_INV ; 
 scalar_t__ BYT_RT5651_MAP (int) ; 
 int BYT_RT5651_MCLK_25MHZ ; 
 int BYT_RT5651_MCLK_EN ; 
 int BYT_RT5651_MONO_SPEAKER ; 
 int /*<<< orphan*/  BYT_RT5651_OVCD_SF (int) ; 
 int BYT_RT5651_OVCD_TH (int) ; 
 int BYT_RT5651_SSP0_AIF1 ; 
 int BYT_RT5651_SSP0_AIF2 ; 
 int BYT_RT5651_SSP2_AIF2 ; 
 int byt_rt5651_quirk ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 

__attribute__((used)) static void log_quirks(struct device *dev)
{
	if (BYT_RT5651_MAP(byt_rt5651_quirk) == BYT_RT5651_DMIC_MAP)
		dev_info(dev, "quirk DMIC_MAP enabled");
	if (BYT_RT5651_MAP(byt_rt5651_quirk) == BYT_RT5651_IN1_MAP)
		dev_info(dev, "quirk IN1_MAP enabled");
	if (BYT_RT5651_MAP(byt_rt5651_quirk) == BYT_RT5651_IN2_MAP)
		dev_info(dev, "quirk IN2_MAP enabled");
	if (BYT_RT5651_MAP(byt_rt5651_quirk) == BYT_RT5651_IN1_IN2_MAP)
		dev_info(dev, "quirk IN1_IN2_MAP enabled");
	if (BYT_RT5651_JDSRC(byt_rt5651_quirk)) {
		dev_info(dev, "quirk realtek,jack-detect-source %ld\n",
			 BYT_RT5651_JDSRC(byt_rt5651_quirk));
		dev_info(dev, "quirk realtek,over-current-threshold-microamp %ld\n",
			 BYT_RT5651_OVCD_TH(byt_rt5651_quirk) * 100);
		dev_info(dev, "quirk realtek,over-current-scale-factor %ld\n",
			 BYT_RT5651_OVCD_SF(byt_rt5651_quirk));
	}
	if (byt_rt5651_quirk & BYT_RT5651_DMIC_EN)
		dev_info(dev, "quirk DMIC enabled");
	if (byt_rt5651_quirk & BYT_RT5651_MCLK_EN)
		dev_info(dev, "quirk MCLK_EN enabled");
	if (byt_rt5651_quirk & BYT_RT5651_MCLK_25MHZ)
		dev_info(dev, "quirk MCLK_25MHZ enabled");
	if (byt_rt5651_quirk & BYT_RT5651_SSP2_AIF2)
		dev_info(dev, "quirk SSP2_AIF2 enabled\n");
	if (byt_rt5651_quirk & BYT_RT5651_SSP0_AIF1)
		dev_info(dev, "quirk SSP0_AIF1 enabled\n");
	if (byt_rt5651_quirk & BYT_RT5651_SSP0_AIF2)
		dev_info(dev, "quirk SSP0_AIF2 enabled\n");
	if (byt_rt5651_quirk & BYT_RT5651_MONO_SPEAKER)
		dev_info(dev, "quirk MONO_SPEAKER enabled\n");
	if (byt_rt5651_quirk & BYT_RT5651_JD_NOT_INV)
		dev_info(dev, "quirk JD_NOT_INV enabled\n");
}