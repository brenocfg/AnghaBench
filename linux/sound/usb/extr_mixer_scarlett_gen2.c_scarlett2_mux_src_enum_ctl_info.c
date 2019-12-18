#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* mixer; } ;
struct usb_mixer_elem_info {int /*<<< orphan*/  channels; TYPE_2__ head; } ;
struct snd_kcontrol {struct usb_mixer_elem_info* private_data; } ;
struct TYPE_9__ {unsigned int item; int items; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {TYPE_4__ enumerated; } ;
struct snd_ctl_elem_info {TYPE_5__ value; int /*<<< orphan*/  count; int /*<<< orphan*/  type; } ;
struct scarlett2_ports {unsigned int* num; char* src_descr; scalar_t__ src_num_offset; } ;
struct scarlett2_mixer_data {int num_mux_srcs; TYPE_3__* info; } ;
struct TYPE_8__ {struct scarlett2_ports* ports; } ;
struct TYPE_6__ {struct scarlett2_mixer_data* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t SCARLETT2_PORT_IN ; 
 int SCARLETT2_PORT_TYPE_COUNT ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_ENUMERATED ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int scarlett2_mux_src_enum_ctl_info(struct snd_kcontrol *kctl,
					   struct snd_ctl_elem_info *uinfo)
{
	struct usb_mixer_elem_info *elem = kctl->private_data;
	struct scarlett2_mixer_data *private = elem->head.mixer->private_data;
	const struct scarlett2_ports *ports = private->info->ports;
	unsigned int item = uinfo->value.enumerated.item;
	int items = private->num_mux_srcs;
	int port_type;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = elem->channels;
	uinfo->value.enumerated.items = items;

	if (item >= items)
		item = uinfo->value.enumerated.item = items - 1;

	for (port_type = 0;
	     port_type < SCARLETT2_PORT_TYPE_COUNT;
	     port_type++) {
		if (item < ports[port_type].num[SCARLETT2_PORT_IN]) {
			sprintf(uinfo->value.enumerated.name,
				ports[port_type].src_descr,
				item + ports[port_type].src_num_offset);
			return 0;
		}
		item -= ports[port_type].num[SCARLETT2_PORT_IN];
	}

	return -EINVAL;
}