#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {struct snd_soc_card* card; TYPE_1__* codec_dai; } ;
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {int dummy; } ;
struct abe_twl6040 {scalar_t__ jack_detection; } ;
struct TYPE_2__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_JACK_HEADSET ; 
 int /*<<< orphan*/  TWL6040_HSF_TRIM_LEFT (int) ; 
 int /*<<< orphan*/  TWL6040_HSF_TRIM_RIGHT (int) ; 
 int /*<<< orphan*/  TWL6040_TRIM_HSOTRIM ; 
 int /*<<< orphan*/  hs_jack ; 
 int /*<<< orphan*/  hs_jack_pins ; 
 int /*<<< orphan*/  omap_mcpdm_configure_dn_offsets (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct abe_twl6040* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int snd_soc_card_jack_new (struct snd_soc_card*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int twl6040_get_trim_value (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl6040_hs_jack_detect (struct snd_soc_component*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_abe_twl6040_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_component *component = rtd->codec_dai->component;
	struct snd_soc_card *card = rtd->card;
	struct abe_twl6040 *priv = snd_soc_card_get_drvdata(card);
	int hs_trim;
	int ret = 0;

	/*
	 * Configure McPDM offset cancellation based on the HSOTRIM value from
	 * twl6040.
	 */
	hs_trim = twl6040_get_trim_value(component, TWL6040_TRIM_HSOTRIM);
	omap_mcpdm_configure_dn_offsets(rtd, TWL6040_HSF_TRIM_LEFT(hs_trim),
					TWL6040_HSF_TRIM_RIGHT(hs_trim));

	/* Headset jack detection only if it is supported */
	if (priv->jack_detection) {
		ret = snd_soc_card_jack_new(rtd->card, "Headset Jack",
					    SND_JACK_HEADSET, &hs_jack,
					    hs_jack_pins,
					    ARRAY_SIZE(hs_jack_pins));
		if (ret)
			return ret;

		twl6040_hs_jack_detect(component, &hs_jack, SND_JACK_HEADSET);
	}

	return 0;
}