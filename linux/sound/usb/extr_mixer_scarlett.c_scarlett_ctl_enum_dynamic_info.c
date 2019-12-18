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
struct usb_mixer_elem_info {int /*<<< orphan*/  channels; struct scarlett_mixer_elem_enum_info* private_data; } ;
struct snd_kcontrol {struct usb_mixer_elem_info* private_data; } ;
struct TYPE_3__ {unsigned int items; unsigned int item; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_info {TYPE_2__ value; int /*<<< orphan*/  count; int /*<<< orphan*/  type; } ;
struct scarlett_mixer_elem_enum_info {unsigned int len; int /*<<< orphan*/  offsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_ENUMERATED ; 
 int /*<<< orphan*/  scarlett_generate_name (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scarlett_ctl_enum_dynamic_info(struct snd_kcontrol *kctl,
					  struct snd_ctl_elem_info *uinfo)
{
	struct usb_mixer_elem_info *elem = kctl->private_data;
	struct scarlett_mixer_elem_enum_info *opt = elem->private_data;
	unsigned int items = opt->len;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = elem->channels;
	uinfo->value.enumerated.items = items;

	if (uinfo->value.enumerated.item >= items)
		uinfo->value.enumerated.item = items - 1;

	/* generate name dynamically based on item number and offset info */
	scarlett_generate_name(uinfo->value.enumerated.item,
			       uinfo->value.enumerated.name,
			       opt->offsets);

	return 0;
}