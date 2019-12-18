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
struct wcd9335_codec {int /*<<< orphan*/  sido_input_src; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIDO_SOURCE_RCO_BG ; 
 int /*<<< orphan*/  WCD9335_ANA_BUCK_CTL ; 
 int /*<<< orphan*/  WCD9335_ANA_BUCK_CTL_VOUT_D_IREF_EXT ; 
 int /*<<< orphan*/  WCD9335_ANA_BUCK_CTL_VOUT_D_IREF_MASK ; 
 int /*<<< orphan*/  WCD9335_ANA_BUCK_CTL_VOUT_D_VREF_EXT ; 
 int /*<<< orphan*/  WCD9335_ANA_BUCK_CTL_VOUT_D_VREF_MASK ; 
 int /*<<< orphan*/  WCD9335_ANA_RCO ; 
 int /*<<< orphan*/  WCD9335_ANA_RCO_BG_ENABLE ; 
 int /*<<< orphan*/  WCD9335_ANA_RCO_BG_EN_MASK ; 
 struct wcd9335_codec* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void wcd9335_enable_sido_buck(struct snd_soc_component *component)
{
	struct wcd9335_codec *wcd = dev_get_drvdata(component->dev);

	snd_soc_component_update_bits(component, WCD9335_ANA_RCO,
					WCD9335_ANA_RCO_BG_EN_MASK,
					WCD9335_ANA_RCO_BG_ENABLE);
	snd_soc_component_update_bits(component, WCD9335_ANA_BUCK_CTL,
					WCD9335_ANA_BUCK_CTL_VOUT_D_IREF_MASK,
					WCD9335_ANA_BUCK_CTL_VOUT_D_IREF_EXT);
	/* 100us sleep needed after IREF settings */
	usleep_range(100, 110);
	snd_soc_component_update_bits(component, WCD9335_ANA_BUCK_CTL,
					WCD9335_ANA_BUCK_CTL_VOUT_D_VREF_MASK,
					WCD9335_ANA_BUCK_CTL_VOUT_D_VREF_EXT);
	/* 100us sleep needed after VREF settings */
	usleep_range(100, 110);
	wcd->sido_input_src = SIDO_SOURCE_RCO_BG;
}