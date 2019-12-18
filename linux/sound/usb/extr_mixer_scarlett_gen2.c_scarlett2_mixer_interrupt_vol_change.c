#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_mixer_interface {TYPE_3__* chip; struct scarlett2_mixer_data* private_data; } ;
struct scarlett2_ports {int* num; } ;
struct scarlett2_mixer_data {int vol_updated; TYPE_4__** vol_ctls; int /*<<< orphan*/ * vol_sw_hw_switch; TYPE_2__* master_vol_ctl; TYPE_1__* info; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
struct TYPE_7__ {int /*<<< orphan*/  card; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {struct scarlett2_ports* ports; } ;

/* Variables and functions */
 size_t SCARLETT2_PORT_OUT ; 
 size_t SCARLETT2_PORT_TYPE_ANALOGUE ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_VALUE ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scarlett2_mixer_interrupt_vol_change(
	struct usb_mixer_interface *mixer)
{
	struct scarlett2_mixer_data *private = mixer->private_data;
	const struct scarlett2_ports *ports = private->info->ports;
	int num_line_out =
		ports[SCARLETT2_PORT_TYPE_ANALOGUE].num[SCARLETT2_PORT_OUT];
	int i;

	private->vol_updated = 1;

	snd_ctl_notify(mixer->chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
		       &private->master_vol_ctl->id);

	for (i = 0; i < num_line_out; i++) {
		if (!private->vol_sw_hw_switch[i])
			continue;
		snd_ctl_notify(mixer->chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &private->vol_ctls[i]->id);
	}
}