#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; TYPE_2__* dpcm; int /*<<< orphan*/  fe_compr; TYPE_1__* dai_link; struct snd_soc_card* card; } ;
struct snd_soc_dapm_widget_list {int num_widgets; TYPE_3__** widgets; } ;
struct snd_soc_card {int dummy; } ;
struct TYPE_6__ {int id; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  runtime_update; int /*<<< orphan*/  runtime; } ;
struct TYPE_4__ {int /*<<< orphan*/  no_pcm; } ;

/* Variables and functions */
 int SNDRV_PCM_STREAM_CAPTURE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SND_SOC_DPCM_UPDATE_BE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int dpcm_be_connect (struct snd_soc_pcm_runtime*,struct snd_soc_pcm_runtime*,int) ; 
 struct snd_soc_pcm_runtime* dpcm_get_be (struct snd_soc_card*,TYPE_3__*,int) ; 
#define  snd_soc_dapm_dai_in 129 
#define  snd_soc_dapm_dai_out 128 

__attribute__((used)) static int dpcm_add_paths(struct snd_soc_pcm_runtime *fe, int stream,
	struct snd_soc_dapm_widget_list **list_)
{
	struct snd_soc_card *card = fe->card;
	struct snd_soc_dapm_widget_list *list = *list_;
	struct snd_soc_pcm_runtime *be;
	int i, new = 0, err;

	/* Create any new FE <--> BE connections */
	for (i = 0; i < list->num_widgets; i++) {

		switch (list->widgets[i]->id) {
		case snd_soc_dapm_dai_in:
			if (stream != SNDRV_PCM_STREAM_PLAYBACK)
				continue;
			break;
		case snd_soc_dapm_dai_out:
			if (stream != SNDRV_PCM_STREAM_CAPTURE)
				continue;
			break;
		default:
			continue;
		}

		/* is there a valid BE rtd for this widget */
		be = dpcm_get_be(card, list->widgets[i], stream);
		if (!be) {
			dev_err(fe->dev, "ASoC: no BE found for %s\n",
					list->widgets[i]->name);
			continue;
		}

		/* make sure BE is a real BE */
		if (!be->dai_link->no_pcm)
			continue;

		/* don't connect if FE is not running */
		if (!fe->dpcm[stream].runtime && !fe->fe_compr)
			continue;

		/* newly connected FE and BE */
		err = dpcm_be_connect(fe, be, stream);
		if (err < 0) {
			dev_err(fe->dev, "ASoC: can't connect %s\n",
				list->widgets[i]->name);
			break;
		} else if (err == 0) /* already connected */
			continue;

		/* new */
		be->dpcm[stream].runtime_update = SND_SOC_DPCM_UPDATE_BE;
		new++;
	}

	dev_dbg(fe->dev, "ASoC: found %d new BE paths\n", new);
	return new;
}