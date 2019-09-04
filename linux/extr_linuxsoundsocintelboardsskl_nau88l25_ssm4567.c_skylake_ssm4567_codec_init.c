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
struct snd_soc_pcm_runtime {int /*<<< orphan*/ * codec_dais; } ;

/* Variables and functions */
 int snd_soc_dai_set_tdm_slot (int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static int skylake_ssm4567_codec_init(struct snd_soc_pcm_runtime *rtd)
{
	int ret;

	/* Slot 1 for left */
	ret = snd_soc_dai_set_tdm_slot(rtd->codec_dais[0], 0x01, 0x01, 2, 48);
	if (ret < 0)
		return ret;

	/* Slot 2 for right */
	ret = snd_soc_dai_set_tdm_slot(rtd->codec_dais[1], 0x02, 0x02, 2, 48);
	if (ret < 0)
		return ret;

	return ret;
}