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
typedef  int /*<<< orphan*/  template ;
struct snd_soc_pcm_runtime {TYPE_1__* dai_link; } ;
struct snd_soc_dapm_widget {char* name; int event_flags; int num_kcontrols; int /*<<< orphan*/ * kcontrol_news; struct snd_pcm_substream* priv; int /*<<< orphan*/  event; int /*<<< orphan*/  id; int /*<<< orphan*/  reg; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; int /*<<< orphan*/  dapm; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_2__ {int num_params; int /*<<< orphan*/  params; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct snd_soc_dapm_widget* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct snd_soc_dapm_widget*) ; 
 int PTR_ERR (struct snd_soc_dapm_widget*) ; 
 int SND_SOC_DAPM_POST_PMD ; 
 int SND_SOC_DAPM_POST_PMU ; 
 int SND_SOC_DAPM_PRE_PMD ; 
 int SND_SOC_DAPM_PRE_PMU ; 
 int /*<<< orphan*/  SND_SOC_NOPM ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 char* devm_kasprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 char** devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct snd_soc_dapm_widget*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_dai_link_event ; 
 int /*<<< orphan*/ * snd_soc_dapm_alloc_kcontrol (struct snd_soc_card*,char*,int /*<<< orphan*/ ,int,char const**,unsigned long*) ; 
 int /*<<< orphan*/  snd_soc_dapm_dai_link ; 
 int /*<<< orphan*/  snd_soc_dapm_free_kcontrol (struct snd_soc_card*,unsigned long*,int,char const**) ; 
 struct snd_soc_dapm_widget* snd_soc_dapm_new_control_unlocked (int /*<<< orphan*/ *,struct snd_soc_dapm_widget*) ; 

__attribute__((used)) static struct snd_soc_dapm_widget *
snd_soc_dapm_new_dai(struct snd_soc_card *card,
		     struct snd_pcm_substream *substream,
		     char *id)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dapm_widget template;
	struct snd_soc_dapm_widget *w;
	const char **w_param_text;
	unsigned long private_value = 0;
	char *link_name;
	int ret;

	link_name = devm_kasprintf(card->dev, GFP_KERNEL, "%s-%s",
				   rtd->dai_link->name, id);
	if (!link_name)
		return ERR_PTR(-ENOMEM);

	memset(&template, 0, sizeof(template));
	template.reg = SND_SOC_NOPM;
	template.id = snd_soc_dapm_dai_link;
	template.name = link_name;
	template.event = snd_soc_dai_link_event;
	template.event_flags = SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD;
	template.kcontrol_news = NULL;

	/* allocate memory for control, only in case of multiple configs */
	if (rtd->dai_link->num_params > 1) {
		w_param_text = devm_kcalloc(card->dev,
					    rtd->dai_link->num_params,
					    sizeof(char *), GFP_KERNEL);
		if (!w_param_text) {
			ret = -ENOMEM;
			goto param_fail;
		}

		template.num_kcontrols = 1;
		template.kcontrol_news =
					snd_soc_dapm_alloc_kcontrol(card,
						link_name,
						rtd->dai_link->params,
						rtd->dai_link->num_params,
						w_param_text, &private_value);
		if (!template.kcontrol_news) {
			ret = -ENOMEM;
			goto param_fail;
		}
	} else {
		w_param_text = NULL;
	}
	dev_dbg(card->dev, "ASoC: adding %s widget\n", link_name);

	w = snd_soc_dapm_new_control_unlocked(&card->dapm, &template);
	if (IS_ERR(w)) {
		ret = PTR_ERR(w);
		goto outfree_kcontrol_news;
	}

	w->priv = substream;

	return w;

outfree_kcontrol_news:
	devm_kfree(card->dev, (void *)template.kcontrol_news);
	snd_soc_dapm_free_kcontrol(card, &private_value,
				   rtd->dai_link->num_params, w_param_text);
param_fail:
	devm_kfree(card->dev, link_name);
	return ERR_PTR(ret);
}