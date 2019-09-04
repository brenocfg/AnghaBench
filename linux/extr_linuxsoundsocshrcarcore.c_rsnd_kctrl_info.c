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
struct snd_kcontrol {int dummy; } ;
struct TYPE_5__ {int max; scalar_t__ min; } ;
struct TYPE_4__ {int items; int item; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_2__ integer; TYPE_1__ enumerated; } ;
struct snd_ctl_elem_info {int /*<<< orphan*/  type; TYPE_3__ value; int /*<<< orphan*/  count; } ;
struct rsnd_kctrl_cfg {int max; int /*<<< orphan*/  size; int /*<<< orphan*/ * texts; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_BOOLEAN ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_ENUMERATED ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 
 struct rsnd_kctrl_cfg* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rsnd_kctrl_info(struct snd_kcontrol *kctrl,
			   struct snd_ctl_elem_info *uinfo)
{
	struct rsnd_kctrl_cfg *cfg = snd_kcontrol_chip(kctrl);

	if (cfg->texts) {
		uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
		uinfo->count = cfg->size;
		uinfo->value.enumerated.items = cfg->max;
		if (uinfo->value.enumerated.item >= cfg->max)
			uinfo->value.enumerated.item = cfg->max - 1;
		strlcpy(uinfo->value.enumerated.name,
			cfg->texts[uinfo->value.enumerated.item],
			sizeof(uinfo->value.enumerated.name));
	} else {
		uinfo->count = cfg->size;
		uinfo->value.integer.min = 0;
		uinfo->value.integer.max = cfg->max;
		uinfo->type = (cfg->max == 1) ?
			SNDRV_CTL_ELEM_TYPE_BOOLEAN :
			SNDRV_CTL_ELEM_TYPE_INTEGER;
	}

	return 0;
}