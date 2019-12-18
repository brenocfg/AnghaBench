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
 int /*<<< orphan*/  SND_JACK_HEADPHONE ; 
 int /*<<< orphan*/  hs_jack ; 
 int /*<<< orphan*/  hs_jack_gpio ; 
 int /*<<< orphan*/  hs_jack_pin ; 
 int snd_soc_card_jack_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_jack_add_gpios (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hx4700_ak4641_init(struct snd_soc_pcm_runtime *rtd)
{
	int err;

	/* Jack detection API stuff */
	err = snd_soc_card_jack_new(rtd->card, "Headphone Jack",
				    SND_JACK_HEADPHONE, &hs_jack, hs_jack_pin,
				    ARRAY_SIZE(hs_jack_pin));
	if (err)
		return err;

	err = snd_soc_jack_add_gpios(&hs_jack, 1, &hs_jack_gpio);

	return err;
}