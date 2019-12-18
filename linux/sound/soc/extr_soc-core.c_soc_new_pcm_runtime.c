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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  codec_dais; struct snd_soc_dai_link* dai_link; struct snd_soc_card* card; int /*<<< orphan*/  component_list; } ;
struct snd_soc_dai_link {int /*<<< orphan*/  num_codecs; int /*<<< orphan*/ * ops; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_soc_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_soc_pcm_runtime*) ; 
 struct snd_soc_pcm_runtime* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_snd_soc_ops ; 

__attribute__((used)) static struct snd_soc_pcm_runtime *soc_new_pcm_runtime(
	struct snd_soc_card *card, struct snd_soc_dai_link *dai_link)
{
	struct snd_soc_pcm_runtime *rtd;

	rtd = kzalloc(sizeof(struct snd_soc_pcm_runtime), GFP_KERNEL);
	if (!rtd)
		return NULL;

	INIT_LIST_HEAD(&rtd->component_list);
	rtd->card = card;
	rtd->dai_link = dai_link;
	if (!rtd->dai_link->ops)
		rtd->dai_link->ops = &null_snd_soc_ops;

	rtd->codec_dais = kcalloc(dai_link->num_codecs,
					sizeof(struct snd_soc_dai *),
					GFP_KERNEL);
	if (!rtd->codec_dais) {
		kfree(rtd);
		return NULL;
	}

	return rtd;
}