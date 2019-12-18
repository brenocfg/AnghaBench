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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; TYPE_2__* card; } ;
struct snd_soc_jack {int dummy; } ;
struct cht_mc_private {int quirks; int /*<<< orphan*/  mclk; scalar_t__ ts3a227e_present; struct snd_soc_jack jack; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHT_PLAT_CLK_3_HZ ; 
 int QUIRK_PMC_PLT_CLK_0 ; 
 int SND_JACK_HEADPHONE ; 
 int SND_JACK_MICROPHONE ; 
 int /*<<< orphan*/  cht_jack_nb ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hs_jack_gpios ; 
 int /*<<< orphan*/  hs_jack_pins ; 
 struct cht_mc_private* snd_soc_card_get_drvdata (TYPE_2__*) ; 
 int snd_soc_card_jack_new (TYPE_2__*,char*,int,struct snd_soc_jack*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_jack_add_gpiods (int /*<<< orphan*/ ,struct snd_soc_jack*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_jack_notifier_register (struct snd_soc_jack*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cht_codec_init(struct snd_soc_pcm_runtime *runtime)
{
	int ret;
	int jack_type;
	struct cht_mc_private *ctx = snd_soc_card_get_drvdata(runtime->card);
	struct snd_soc_jack *jack = &ctx->jack;

	if (ctx->ts3a227e_present) {
		/*
		 * The jack has already been created in the
		 * cht_max98090_headset_init() function.
		 */
		snd_soc_jack_notifier_register(jack, &cht_jack_nb);
		return 0;
	}

	jack_type = SND_JACK_HEADPHONE | SND_JACK_MICROPHONE;

	ret = snd_soc_card_jack_new(runtime->card, "Headset Jack",
				    jack_type, jack,
				    hs_jack_pins, ARRAY_SIZE(hs_jack_pins));
	if (ret) {
		dev_err(runtime->dev, "Headset Jack creation failed %d\n", ret);
		return ret;
	}

	ret = snd_soc_jack_add_gpiods(runtime->card->dev->parent, jack,
				      ARRAY_SIZE(hs_jack_gpios),
				      hs_jack_gpios);
	if (ret) {
		/*
		 * flag error but don't bail if jack detect is broken
		 * due to platform issues or bad BIOS/configuration
		 */
		dev_err(runtime->dev,
			"jack detection gpios not added, error %d\n", ret);
	}

	/* See the comment in snd_cht_mc_probe() */
	if (ctx->quirks & QUIRK_PMC_PLT_CLK_0)
		return 0;

	/*
	 * The firmware might enable the clock at
	 * boot (this information may or may not
	 * be reflected in the enable clock register).
	 * To change the rate we must disable the clock
	 * first to cover these cases. Due to common
	 * clock framework restrictions that do not allow
	 * to disable a clock that has not been enabled,
	 * we need to enable the clock first.
	 */
	ret = clk_prepare_enable(ctx->mclk);
	if (!ret)
		clk_disable_unprepare(ctx->mclk);

	ret = clk_set_rate(ctx->mclk, CHT_PLAT_CLK_3_HZ);

	if (ret)
		dev_err(runtime->dev, "unable to set MCLK rate\n");

	return ret;
}