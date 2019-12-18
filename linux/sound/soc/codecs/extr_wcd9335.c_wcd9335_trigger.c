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
struct slim_stream_config {int dummy; } ;
struct wcd_slim_codec_dai_data {int /*<<< orphan*/  sruntime; struct slim_stream_config sconfig; } ;
struct wcd9335_codec {struct wcd_slim_codec_dai_data* dai; } ;
struct snd_soc_dai {size_t id; int /*<<< orphan*/  component; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  slim_stream_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slim_stream_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slim_stream_prepare (int /*<<< orphan*/ ,struct slim_stream_config*) ; 
 int /*<<< orphan*/  slim_stream_unprepare (int /*<<< orphan*/ ) ; 
 struct wcd9335_codec* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wcd9335_trigger(struct snd_pcm_substream *substream, int cmd,
			   struct snd_soc_dai *dai)
{
	struct wcd_slim_codec_dai_data *dai_data;
	struct wcd9335_codec *wcd;
	struct slim_stream_config *cfg;

	wcd = snd_soc_component_get_drvdata(dai->component);

	dai_data = &wcd->dai[dai->id];

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		cfg = &dai_data->sconfig;
		slim_stream_prepare(dai_data->sruntime, cfg);
		slim_stream_enable(dai_data->sruntime);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		slim_stream_unprepare(dai_data->sruntime);
		slim_stream_disable(dai_data->sruntime);
		break;
	default:
		break;
	}

	return 0;
}