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
struct snd_kcontrol {scalar_t__ private_value; } ;
struct snd_emu10k1_fx8010_ctl {scalar_t__ min; int max; int /*<<< orphan*/  vcount; } ;
struct TYPE_3__ {scalar_t__ min; int max; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_info {TYPE_2__ value; int /*<<< orphan*/  count; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_BOOLEAN ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 

__attribute__((used)) static int snd_emu10k1_gpr_ctl_info(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
	struct snd_emu10k1_fx8010_ctl *ctl =
		(struct snd_emu10k1_fx8010_ctl *) kcontrol->private_value;

	if (ctl->min == 0 && ctl->max == 1)
		uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	else
		uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = ctl->vcount;
	uinfo->value.integer.min = ctl->min;
	uinfo->value.integer.max = ctl->max;
	return 0;
}