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
struct snd_ac97_template {int /*<<< orphan*/  scaps; scalar_t__ num; struct aaci* private_data; } ;
struct snd_ac97_bus {int clock; int /*<<< orphan*/ * pcms; } ;
struct snd_ac97 {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pcm; } ;
struct TYPE_3__ {int /*<<< orphan*/ * pcm; } ;
struct aaci {TYPE_2__ capture; TYPE_1__ playback; struct snd_ac97* ac97; struct snd_ac97_bus* ac97_bus; int /*<<< orphan*/  card; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ AACI_RESET ; 
 int /*<<< orphan*/  AC97_PC_BEEP ; 
 int /*<<< orphan*/  AC97_SCAP_SKIP_MODEM ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int FRAME_PERIOD_US ; 
 int /*<<< orphan*/  RESET_NRST ; 
 int /*<<< orphan*/  aaci_bus_ops ; 
 int /*<<< orphan*/  ac97_defs ; 
 scalar_t__ ac97_is_audio (struct snd_ac97*) ; 
 int /*<<< orphan*/  memset (struct snd_ac97_template*,int /*<<< orphan*/ ,int) ; 
 int snd_ac97_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct aaci*,struct snd_ac97_bus**) ; 
 int snd_ac97_mixer (struct snd_ac97_bus*,struct snd_ac97_template*,struct snd_ac97**) ; 
 int snd_ac97_pcm_assign (struct snd_ac97_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int aaci_probe_ac97(struct aaci *aaci)
{
	struct snd_ac97_template ac97_template;
	struct snd_ac97_bus *ac97_bus;
	struct snd_ac97 *ac97;
	int ret;

	/*
	 * Assert AACIRESET for 2us
	 */
	writel(0, aaci->base + AACI_RESET);
	udelay(2);
	writel(RESET_NRST, aaci->base + AACI_RESET);

	/*
	 * Give the AC'97 codec more than enough time
	 * to wake up. (42us = ~2 frames at 48kHz.)
	 */
	udelay(FRAME_PERIOD_US * 2);

	ret = snd_ac97_bus(aaci->card, 0, &aaci_bus_ops, aaci, &ac97_bus);
	if (ret)
		goto out;

	ac97_bus->clock = 48000;
	aaci->ac97_bus = ac97_bus;

	memset(&ac97_template, 0, sizeof(struct snd_ac97_template));
	ac97_template.private_data = aaci;
	ac97_template.num = 0;
	ac97_template.scaps = AC97_SCAP_SKIP_MODEM;

	ret = snd_ac97_mixer(ac97_bus, &ac97_template, &ac97);
	if (ret)
		goto out;
	aaci->ac97 = ac97;

	/*
	 * Disable AC97 PC Beep input on audio codecs.
	 */
	if (ac97_is_audio(ac97))
		snd_ac97_write_cache(ac97, AC97_PC_BEEP, 0x801e);

	ret = snd_ac97_pcm_assign(ac97_bus, ARRAY_SIZE(ac97_defs), ac97_defs);
	if (ret)
		goto out;

	aaci->playback.pcm = &ac97_bus->pcms[0];
	aaci->capture.pcm  = &ac97_bus->pcms[1];

 out:
	return ret;
}