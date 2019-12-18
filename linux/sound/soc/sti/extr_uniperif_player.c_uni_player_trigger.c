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
struct uniperif {int dummy; } ;
struct TYPE_2__ {struct uniperif* uni; } ;
struct sti_uniperiph_data {TYPE_1__ dai_data; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_RESUME 130 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 struct sti_uniperiph_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int uni_player_resume (struct uniperif*) ; 
 int uni_player_start (struct uniperif*) ; 
 int uni_player_stop (struct uniperif*) ; 

__attribute__((used)) static int uni_player_trigger(struct snd_pcm_substream *substream,
			      int cmd, struct snd_soc_dai *dai)
{
	struct sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	struct uniperif *player = priv->dai_data.uni;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		return uni_player_start(player);
	case SNDRV_PCM_TRIGGER_STOP:
		return uni_player_stop(player);
	case SNDRV_PCM_TRIGGER_RESUME:
		return uni_player_resume(player);
	default:
		return -EINVAL;
	}
}