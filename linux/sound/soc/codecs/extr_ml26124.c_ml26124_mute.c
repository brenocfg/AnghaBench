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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct ml26124_priv {TYPE_1__* substream; } ;
struct TYPE_2__ {int stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int DVOL_CTL_DVMUTE_OFF ; 
 int DVOL_CTL_DVMUTE_ON ; 
 int /*<<< orphan*/  ML26124_DVOL_CTL ; 
 int /*<<< orphan*/  ML26124_REC_PLYBAK_RUN ; 
#define  SNDRV_PCM_STREAM_CAPTURE 129 
#define  SNDRV_PCM_STREAM_PLAYBACK 128 
 struct ml26124_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ml26124_mute(struct snd_soc_dai *dai, int mute)
{
	struct snd_soc_component *component = dai->component;
	struct ml26124_priv *priv = snd_soc_component_get_drvdata(component);

	switch (priv->substream->stream) {
	case SNDRV_PCM_STREAM_CAPTURE:
		snd_soc_component_update_bits(component, ML26124_REC_PLYBAK_RUN, BIT(0), 1);
		break;
	case SNDRV_PCM_STREAM_PLAYBACK:
		snd_soc_component_update_bits(component, ML26124_REC_PLYBAK_RUN, BIT(1), 2);
		break;
	}

	if (mute)
		snd_soc_component_update_bits(component, ML26124_DVOL_CTL, BIT(4),
				    DVOL_CTL_DVMUTE_ON);
	else
		snd_soc_component_update_bits(component, ML26124_DVOL_CTL, BIT(4),
				    DVOL_CTL_DVMUTE_OFF);

	return 0;
}