#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wcd9335_codec {int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  WCD9335_CODEC_RPM_CLK_GATE ; 
 int /*<<< orphan*/  WCD9335_CODEC_RPM_CLK_GATE_MCLK_GATE_MASK ; 
 int /*<<< orphan*/  WCD9335_CODEC_RPM_CLK_MCLK_CFG ; 
 int /*<<< orphan*/  WCD9335_CODEC_RPM_CLK_MCLK_CFG_9P6MHZ ; 
 int /*<<< orphan*/  WCD9335_CODEC_RPM_CLK_MCLK_CFG_MCLK_MASK ; 
 struct wcd9335_codec* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* wcd9335_codec_reg_init ; 
 int /*<<< orphan*/  wcd9335_enable_efuse_sensing (struct snd_soc_component*) ; 

__attribute__((used)) static void wcd9335_codec_init(struct snd_soc_component *component)
{
	struct wcd9335_codec *wcd = dev_get_drvdata(component->dev);
	int i;

	/* ungate MCLK and set clk rate */
	regmap_update_bits(wcd->regmap, WCD9335_CODEC_RPM_CLK_GATE,
				WCD9335_CODEC_RPM_CLK_GATE_MCLK_GATE_MASK, 0);

	regmap_update_bits(wcd->regmap, WCD9335_CODEC_RPM_CLK_MCLK_CFG,
				WCD9335_CODEC_RPM_CLK_MCLK_CFG_MCLK_MASK,
				WCD9335_CODEC_RPM_CLK_MCLK_CFG_9P6MHZ);

	for (i = 0; i < ARRAY_SIZE(wcd9335_codec_reg_init); i++)
		snd_soc_component_update_bits(component,
					wcd9335_codec_reg_init[i].reg,
					wcd9335_codec_reg_init[i].mask,
					wcd9335_codec_reg_init[i].val);

	wcd9335_enable_efuse_sensing(component);
}