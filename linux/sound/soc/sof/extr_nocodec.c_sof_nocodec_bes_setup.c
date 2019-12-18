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
struct snd_sof_dsp_ops {TYPE_1__* drv; } ;
struct snd_soc_dai_link_component {char* dai_name; char* name; } ;
struct snd_soc_dai_link {int num_cpus; int num_codecs; int num_platforms; int id; int no_pcm; int dpcm_playback; int dpcm_capture; struct snd_soc_dai_link_component* codecs; struct snd_soc_dai_link_component* platforms; struct snd_soc_dai_link_component* cpus; int /*<<< orphan*/  name; } ;
struct snd_soc_card {int num_links; struct snd_soc_dai_link* dai_link; } ;
struct device {int dummy; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,int) ; 
 struct snd_soc_dai_link_component* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sof_nocodec_bes_setup(struct device *dev,
				 const struct snd_sof_dsp_ops *ops,
				 struct snd_soc_dai_link *links,
				 int link_num, struct snd_soc_card *card)
{
	struct snd_soc_dai_link_component *dlc;
	int i;

	if (!ops || !links || !card)
		return -EINVAL;

	/* set up BE dai_links */
	for (i = 0; i < link_num; i++) {
		dlc = devm_kzalloc(dev, 3 * sizeof(*dlc), GFP_KERNEL);
		if (!dlc)
			return -ENOMEM;

		links[i].name = devm_kasprintf(dev, GFP_KERNEL,
					       "NoCodec-%d", i);
		if (!links[i].name)
			return -ENOMEM;

		links[i].cpus = &dlc[0];
		links[i].codecs = &dlc[1];
		links[i].platforms = &dlc[2];

		links[i].num_cpus = 1;
		links[i].num_codecs = 1;
		links[i].num_platforms = 1;

		links[i].id = i;
		links[i].no_pcm = 1;
		links[i].cpus->dai_name = ops->drv[i].name;
		links[i].platforms->name = dev_name(dev);
		links[i].codecs->dai_name = "snd-soc-dummy-dai";
		links[i].codecs->name = "snd-soc-dummy";
		links[i].dpcm_playback = 1;
		links[i].dpcm_capture = 1;
	}

	card->dai_link = links;
	card->num_links = link_num;

	return 0;
}