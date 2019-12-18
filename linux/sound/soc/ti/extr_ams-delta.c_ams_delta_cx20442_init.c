#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {struct snd_soc_dai* codec_dai; struct snd_soc_card* card; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_dai {TYPE_1__* driver; int /*<<< orphan*/  component; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; struct snd_soc_dapm_context dapm; } ;
struct TYPE_4__ {int /*<<< orphan*/  shutdown; int /*<<< orphan*/  startup; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  N_V253 ; 
 int /*<<< orphan*/  SND_JACK_HEADSET ; 
 int /*<<< orphan*/  ams_delta_dai_ops ; 
 int /*<<< orphan*/  ams_delta_hook_switch ; 
 int /*<<< orphan*/  ams_delta_hook_switch_gpios ; 
 TYPE_2__ ams_delta_ops ; 
 int /*<<< orphan*/  ams_delta_shutdown ; 
 int /*<<< orphan*/  ams_delta_startup ; 
 int /*<<< orphan*/  cx20442_codec ; 
 int /*<<< orphan*/  cx81801_ops ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_modem_codec ; 
 int snd_soc_card_jack_new (struct snd_soc_card*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_dapm_context*,char*) ; 
 int snd_soc_jack_add_gpiods (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tty_register_ldisc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ams_delta_cx20442_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	struct snd_soc_card *card = rtd->card;
	struct snd_soc_dapm_context *dapm = &card->dapm;
	int ret;
	/* Codec is ready, now add/activate board specific controls */

	/* Store a pointer to the codec structure for tty ldisc use */
	cx20442_codec = rtd->codec_dai->component;

	/* Add hook switch - can be used to control the codec from userspace
	 * even if line discipline fails */
	ret = snd_soc_card_jack_new(card, "hook_switch", SND_JACK_HEADSET,
				    &ams_delta_hook_switch, NULL, 0);
	if (ret)
		dev_warn(card->dev,
				"Failed to allocate resources for hook switch, "
				"will continue without one.\n");
	else {
		ret = snd_soc_jack_add_gpiods(card->dev, &ams_delta_hook_switch,
					ARRAY_SIZE(ams_delta_hook_switch_gpios),
					ams_delta_hook_switch_gpios);
		if (ret)
			dev_warn(card->dev,
				"Failed to set up hook switch GPIO line, "
				"will continue with hook switch inactive.\n");
	}

	gpiod_modem_codec = devm_gpiod_get(card->dev, "modem_codec",
					   GPIOD_OUT_HIGH);
	if (IS_ERR(gpiod_modem_codec)) {
		dev_warn(card->dev, "Failed to obtain modem_codec GPIO\n");
		return 0;
	}

	/* Set up digital mute if not provided by the codec */
	if (!codec_dai->driver->ops) {
		codec_dai->driver->ops = &ams_delta_dai_ops;
	} else {
		ams_delta_ops.startup = ams_delta_startup;
		ams_delta_ops.shutdown = ams_delta_shutdown;
	}

	/* Register optional line discipline for over the modem control */
	ret = tty_register_ldisc(N_V253, &cx81801_ops);
	if (ret) {
		dev_warn(card->dev,
				"Failed to register line discipline, "
				"will continue without any controls.\n");
		return 0;
	}

	/* Set up initial pin constellation */
	snd_soc_dapm_disable_pin(dapm, "Mouthpiece");
	snd_soc_dapm_disable_pin(dapm, "Speaker");
	snd_soc_dapm_disable_pin(dapm, "AGCIN");
	snd_soc_dapm_disable_pin(dapm, "AGCOUT");

	return 0;
}