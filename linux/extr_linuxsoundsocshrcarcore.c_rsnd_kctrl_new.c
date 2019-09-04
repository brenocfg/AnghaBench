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
typedef  int /*<<< orphan*/  u32 ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  num; TYPE_1__* card; } ;
struct snd_kcontrol_new {unsigned char const* name; int /*<<< orphan*/  put; int /*<<< orphan*/  get; int /*<<< orphan*/  index; int /*<<< orphan*/  info; int /*<<< orphan*/  iface; } ;
struct snd_kcontrol {int dummy; } ;
struct snd_card {int dummy; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_kctrl_cfg {char const* const* texts; int size; int (* accept ) (struct rsnd_dai_stream*) ;void (* update ) (struct rsnd_dai_stream*,struct rsnd_mod*) ;struct rsnd_mod* mod; struct rsnd_dai_stream* io; struct snd_kcontrol* kctrl; struct snd_card* card; int /*<<< orphan*/  max; } ;
struct rsnd_dai_stream {int dummy; } ;
struct TYPE_2__ {struct snd_card* snd_card; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int RSND_MAX_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 int /*<<< orphan*/  rsnd_kctrl_get ; 
 int /*<<< orphan*/  rsnd_kctrl_info ; 
 int /*<<< orphan*/  rsnd_kctrl_put ; 
 int snd_ctl_add (struct snd_card*,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_new1 (struct snd_kcontrol_new*,struct rsnd_kctrl_cfg*) ; 

int rsnd_kctrl_new(struct rsnd_mod *mod,
		   struct rsnd_dai_stream *io,
		   struct snd_soc_pcm_runtime *rtd,
		   const unsigned char *name,
		   int (*accept)(struct rsnd_dai_stream *io),
		   void (*update)(struct rsnd_dai_stream *io,
				  struct rsnd_mod *mod),
		   struct rsnd_kctrl_cfg *cfg,
		   const char * const *texts,
		   int size,
		   u32 max)
{
	struct snd_card *card = rtd->card->snd_card;
	struct snd_kcontrol *kctrl;
	struct snd_kcontrol_new knew = {
		.iface		= SNDRV_CTL_ELEM_IFACE_MIXER,
		.name		= name,
		.info		= rsnd_kctrl_info,
		.index		= rtd->num,
		.get		= rsnd_kctrl_get,
		.put		= rsnd_kctrl_put,
	};
	int ret;

	if (size > RSND_MAX_CHANNELS)
		return -EINVAL;

	kctrl = snd_ctl_new1(&knew, cfg);
	if (!kctrl)
		return -ENOMEM;

	ret = snd_ctl_add(card, kctrl);
	if (ret < 0)
		return ret;

	cfg->texts	= texts;
	cfg->max	= max;
	cfg->size	= size;
	cfg->accept	= accept;
	cfg->update	= update;
	cfg->card	= card;
	cfg->kctrl	= kctrl;
	cfg->io		= io;
	cfg->mod	= mod;

	return 0;
}