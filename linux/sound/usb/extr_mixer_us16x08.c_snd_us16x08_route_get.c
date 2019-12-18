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
struct usb_mixer_elem_info {int /*<<< orphan*/ * cache_val; } ;
struct snd_kcontrol {struct usb_mixer_elem_info* private_data; } ;
struct TYPE_5__ {int /*<<< orphan*/ * item; } ;
struct TYPE_6__ {TYPE_2__ enumerated; } ;
struct TYPE_4__ {int index; } ;
struct snd_ctl_elem_value {TYPE_3__ value; TYPE_1__ id; } ;

/* Variables and functions */

__attribute__((used)) static int snd_us16x08_route_get(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct usb_mixer_elem_info *elem = kcontrol->private_data;
	int index = ucontrol->id.index;

	/* route has no bias */
	ucontrol->value.enumerated.item[0] = elem->cache_val[index];

	return 0;
}