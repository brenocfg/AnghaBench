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
struct soc_tplg {int /*<<< orphan*/  dev; TYPE_1__* comp; } ;
struct snd_soc_tplg_link_config {char* name; char* stream_name; int /*<<< orphan*/  flags; int /*<<< orphan*/  flag_mask; scalar_t__ num_hw_configs; int /*<<< orphan*/  id; } ;
struct snd_soc_dai_link {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t SNDRV_CTL_ELEM_ID_NAME_MAXLEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  set_link_flags (struct snd_soc_dai_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_link_hw_format (struct snd_soc_dai_link*,struct snd_soc_tplg_link_config*) ; 
 struct snd_soc_dai_link* snd_soc_find_dai_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*) ; 
 int soc_tplg_dai_link_load (struct soc_tplg*,struct snd_soc_dai_link*,struct snd_soc_tplg_link_config*) ; 
 size_t strnlen (char*,size_t) ; 

__attribute__((used)) static int soc_tplg_link_config(struct soc_tplg *tplg,
	struct snd_soc_tplg_link_config *cfg)
{
	struct snd_soc_dai_link *link;
	const char *name, *stream_name;
	size_t len;
	int ret;

	len = strnlen(cfg->name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN);
	if (len == SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
		return -EINVAL;
	else if (len)
		name = cfg->name;
	else
		name = NULL;

	len = strnlen(cfg->stream_name, SNDRV_CTL_ELEM_ID_NAME_MAXLEN);
	if (len == SNDRV_CTL_ELEM_ID_NAME_MAXLEN)
		return -EINVAL;
	else if (len)
		stream_name = cfg->stream_name;
	else
		stream_name = NULL;

	link = snd_soc_find_dai_link(tplg->comp->card, cfg->id,
				     name, stream_name);
	if (!link) {
		dev_err(tplg->dev, "ASoC: physical link %s (id %d) not exist\n",
			name, cfg->id);
		return -EINVAL;
	}

	/* hw format */
	if (cfg->num_hw_configs)
		set_link_hw_format(link, cfg);

	/* flags */
	if (cfg->flag_mask)
		set_link_flags(link, cfg->flag_mask, cfg->flags);

	/* pass control to component driver for optional further init */
	ret = soc_tplg_dai_link_load(tplg, link, cfg);
	if (ret < 0) {
		dev_err(tplg->dev, "ASoC: physical link loading failed\n");
		return ret;
	}

	return 0;
}