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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dapm_widget_list {int dummy; } ;
struct snd_soc_dai {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  dpcm_end_walk_at_be ; 
 int snd_soc_dapm_dai_get_connected_widgets (struct snd_soc_dai*,int,struct snd_soc_dapm_widget_list**,int /*<<< orphan*/ ) ; 

int dpcm_path_get(struct snd_soc_pcm_runtime *fe,
	int stream, struct snd_soc_dapm_widget_list **list)
{
	struct snd_soc_dai *cpu_dai = fe->cpu_dai;
	int paths;

	/* get number of valid DAI paths and their widgets */
	paths = snd_soc_dapm_dai_get_connected_widgets(cpu_dai, stream, list,
			dpcm_end_walk_at_be);

	dev_dbg(fe->dev, "ASoC: found %d audio %s paths\n", paths,
			stream ? "capture" : "playback");

	return paths;
}