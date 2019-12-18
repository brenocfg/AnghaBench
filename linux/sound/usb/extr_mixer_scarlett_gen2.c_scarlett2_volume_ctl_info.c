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
struct usb_mixer_elem_info {int /*<<< orphan*/  channels; } ;
struct snd_kcontrol {struct usb_mixer_elem_info* private_data; } ;
struct TYPE_4__ {int step; int /*<<< orphan*/  max; scalar_t__ min; } ;
struct TYPE_3__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_info {TYPE_1__ value; int /*<<< orphan*/  count; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCARLETT2_VOLUME_BIAS ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 

__attribute__((used)) static int scarlett2_volume_ctl_info(struct snd_kcontrol *kctl,
				     struct snd_ctl_elem_info *uinfo)
{
	struct usb_mixer_elem_info *elem = kctl->private_data;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = elem->channels;
	uinfo->value.integer.min = 0;
	uinfo->value.integer.max = SCARLETT2_VOLUME_BIAS;
	uinfo->value.integer.step = 1;
	return 0;
}