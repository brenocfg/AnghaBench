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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct es8316_priv {int /*<<< orphan*/  mclk; struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  ES8316_CLKMGR_ADCOSR ; 
 int /*<<< orphan*/  ES8316_RESET ; 
 int ES8316_RESET_CSM_ON ; 
 int /*<<< orphan*/  ES8316_SYS_VMIDSEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devm_clk_get_optional (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct es8316_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int es8316_probe(struct snd_soc_component *component)
{
	struct es8316_priv *es8316 = snd_soc_component_get_drvdata(component);
	int ret;

	es8316->component = component;

	es8316->mclk = devm_clk_get_optional(component->dev, "mclk");
	if (IS_ERR(es8316->mclk)) {
		dev_err(component->dev, "unable to get mclk\n");
		return PTR_ERR(es8316->mclk);
	}
	if (!es8316->mclk)
		dev_warn(component->dev, "assuming static mclk\n");

	ret = clk_prepare_enable(es8316->mclk);
	if (ret) {
		dev_err(component->dev, "unable to enable mclk\n");
		return ret;
	}

	/* Reset codec and enable current state machine */
	snd_soc_component_write(component, ES8316_RESET, 0x3f);
	usleep_range(5000, 5500);
	snd_soc_component_write(component, ES8316_RESET, ES8316_RESET_CSM_ON);
	msleep(30);

	/*
	 * Documentation is unclear, but this value from the vendor driver is
	 * needed otherwise audio output is silent.
	 */
	snd_soc_component_write(component, ES8316_SYS_VMIDSEL, 0xff);

	/*
	 * Documentation for this register is unclear and incomplete,
	 * but here is a vendor-provided value that improves volume
	 * and quality for Intel CHT platforms.
	 */
	snd_soc_component_write(component, ES8316_CLKMGR_ADCOSR, 0x32);

	return 0;
}