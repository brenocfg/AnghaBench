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
struct snd_soc_pcm_runtime {int num_codecs; int /*<<< orphan*/  card; int /*<<< orphan*/ * codec_dais; int /*<<< orphan*/  cpu_dai; } ;

/* Variables and functions */
 int /*<<< orphan*/  dapm_power_widgets (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  soc_dapm_dai_stream_event (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void soc_dapm_stream_event(struct snd_soc_pcm_runtime *rtd, int stream,
	int event)
{
	int i;

	soc_dapm_dai_stream_event(rtd->cpu_dai, stream, event);
	for (i = 0; i < rtd->num_codecs; i++)
		soc_dapm_dai_stream_event(rtd->codec_dais[i], stream, event);

	dapm_power_widgets(rtd->card, event);
}