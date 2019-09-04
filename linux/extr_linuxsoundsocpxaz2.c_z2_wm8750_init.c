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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_JACK_HEADSET ; 
 int /*<<< orphan*/  hs_jack ; 
 int /*<<< orphan*/  hs_jack_gpios ; 
 int /*<<< orphan*/  hs_jack_pins ; 
 int snd_soc_card_jack_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_jack_add_gpios (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int z2_wm8750_init(struct snd_soc_pcm_runtime *rtd)
{
	int ret;

	/* Jack detection API stuff */
	ret = snd_soc_card_jack_new(rtd->card, "Headset Jack", SND_JACK_HEADSET,
				    &hs_jack, hs_jack_pins,
				    ARRAY_SIZE(hs_jack_pins));
	if (ret)
		goto err;

	ret = snd_soc_jack_add_gpios(&hs_jack, ARRAY_SIZE(hs_jack_gpios),
				hs_jack_gpios);
	if (ret)
		goto err;

	return 0;

err:
	return ret;
}