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
 scalar_t__ BYT_CHT_ES8316_INTMIC_IN1_MAP ; 
 scalar_t__ BYT_CHT_ES8316_INTMIC_IN2_MAP ; 
 int BYT_CHT_ES8316_JD_INVERTED ; 
 scalar_t__ BYT_CHT_ES8316_MAP (int) ; 
 int BYT_CHT_ES8316_MONO_SPEAKER ; 
 int BYT_CHT_ES8316_SSP0 ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int quirk ; 

__attribute__((used)) static void log_quirks(struct device *dev)
{
	if (BYT_CHT_ES8316_MAP(quirk) == BYT_CHT_ES8316_INTMIC_IN1_MAP)
		dev_info(dev, "quirk IN1_MAP enabled");
	if (BYT_CHT_ES8316_MAP(quirk) == BYT_CHT_ES8316_INTMIC_IN2_MAP)
		dev_info(dev, "quirk IN2_MAP enabled");
	if (quirk & BYT_CHT_ES8316_SSP0)
		dev_info(dev, "quirk SSP0 enabled");
	if (quirk & BYT_CHT_ES8316_MONO_SPEAKER)
		dev_info(dev, "quirk MONO_SPEAKER enabled\n");
	if (quirk & BYT_CHT_ES8316_JD_INVERTED)
		dev_info(dev, "quirk JD_INVERTED enabled\n");
}