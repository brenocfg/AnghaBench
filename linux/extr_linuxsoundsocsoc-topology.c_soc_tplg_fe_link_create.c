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
struct soc_tplg {TYPE_2__* comp; int /*<<< orphan*/  ops; int /*<<< orphan*/  index; } ;
struct snd_soc_tplg_pcm {int /*<<< orphan*/  flags; int /*<<< orphan*/  flag_mask; int /*<<< orphan*/  capture; int /*<<< orphan*/  playback; int /*<<< orphan*/  dai_name; int /*<<< orphan*/  pcm_id; int /*<<< orphan*/  pcm_name; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; int /*<<< orphan*/  type; int /*<<< orphan*/  ops; int /*<<< orphan*/  index; } ;
struct snd_soc_dai_link {char* codec_name; char* codec_dai_name; int dynamic; TYPE_1__ dobj; int /*<<< orphan*/  dpcm_capture; int /*<<< orphan*/  dpcm_playback; void* cpu_dai_name; int /*<<< orphan*/  id; void* stream_name; void* name; } ;
struct TYPE_4__ {int /*<<< orphan*/  card; int /*<<< orphan*/  dobj_list; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SND_SOC_DOBJ_DAI_LINK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct snd_soc_dai_link*) ; 
 void* kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_dai_link* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_link_flags (struct snd_soc_dai_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_add_dai_link (int /*<<< orphan*/ ,struct snd_soc_dai_link*) ; 
 int soc_tplg_dai_link_load (struct soc_tplg*,struct snd_soc_dai_link*,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int soc_tplg_fe_link_create(struct soc_tplg *tplg,
	struct snd_soc_tplg_pcm *pcm)
{
	struct snd_soc_dai_link *link;
	int ret;

	link = kzalloc(sizeof(struct snd_soc_dai_link), GFP_KERNEL);
	if (link == NULL)
		return -ENOMEM;

	if (strlen(pcm->pcm_name)) {
		link->name = kstrdup(pcm->pcm_name, GFP_KERNEL);
		link->stream_name = kstrdup(pcm->pcm_name, GFP_KERNEL);
	}
	link->id = pcm->pcm_id;

	if (strlen(pcm->dai_name))
		link->cpu_dai_name = kstrdup(pcm->dai_name, GFP_KERNEL);

	link->codec_name = "snd-soc-dummy";
	link->codec_dai_name = "snd-soc-dummy-dai";

	/* enable DPCM */
	link->dynamic = 1;
	link->dpcm_playback = pcm->playback;
	link->dpcm_capture = pcm->capture;
	if (pcm->flag_mask)
		set_link_flags(link, pcm->flag_mask, pcm->flags);

	/* pass control to component driver for optional further init */
	ret = soc_tplg_dai_link_load(tplg, link, NULL);
	if (ret < 0) {
		dev_err(tplg->comp->dev, "ASoC: FE link loading failed\n");
		kfree(link);
		return ret;
	}

	link->dobj.index = tplg->index;
	link->dobj.ops = tplg->ops;
	link->dobj.type = SND_SOC_DOBJ_DAI_LINK;
	list_add(&link->dobj.list, &tplg->comp->dobj_list);

	snd_soc_add_dai_link(tplg->comp->card, link);
	return 0;
}