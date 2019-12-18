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
 int CHT_RT5645_SSP0_AIF1 ; 
 int CHT_RT5645_SSP0_AIF2 ; 
 int CHT_RT5645_SSP2_AIF2 ; 
 int cht_rt5645_quirk ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 

__attribute__((used)) static void log_quirks(struct device *dev)
{
	if (cht_rt5645_quirk & CHT_RT5645_SSP2_AIF2)
		dev_info(dev, "quirk SSP2_AIF2 enabled");
	if (cht_rt5645_quirk & CHT_RT5645_SSP0_AIF1)
		dev_info(dev, "quirk SSP0_AIF1 enabled");
	if (cht_rt5645_quirk & CHT_RT5645_SSP0_AIF2)
		dev_info(dev, "quirk SSP0_AIF2 enabled");
}