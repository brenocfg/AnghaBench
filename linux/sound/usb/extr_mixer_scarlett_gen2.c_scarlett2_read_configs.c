#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void* u8 ;
struct usb_mixer_interface {struct scarlett2_mixer_data* private_data; } ;
struct scarlett2_usb_volume_status {int master_vol; int* sw_vol; int /*<<< orphan*/ * buttons; scalar_t__* sw_hw_switch; } ;
struct scarlett2_ports {int* num; } ;
struct scarlett2_mixer_data {int* vol_sw_hw_switch; int* vol; int* buttons; void* master_vol; void** pad_switch; void** level_switch; struct scarlett2_device_info* info; } ;
struct scarlett2_device_info {int level_input_count; int pad_input_count; int button_count; scalar_t__ line_out_hw_vol; struct scarlett2_ports* ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCARLETT2_CONFIG_LEVEL_SWITCH ; 
 int /*<<< orphan*/  SCARLETT2_CONFIG_PAD_SWITCH ; 
 int SCARLETT2_LEVEL_SWITCH_MAX ; 
 int SCARLETT2_PAD_SWITCH_MAX ; 
 size_t SCARLETT2_PORT_OUT ; 
 size_t SCARLETT2_PORT_TYPE_ANALOGUE ; 
 int SCARLETT2_VOLUME_BIAS ; 
 void* clamp (int,int /*<<< orphan*/ ,int) ; 
 int scarlett2_usb_get_config (struct usb_mixer_interface*,int /*<<< orphan*/ ,int,void**) ; 
 int scarlett2_usb_get_volume_status (struct usb_mixer_interface*,struct scarlett2_usb_volume_status*) ; 

__attribute__((used)) static int scarlett2_read_configs(struct usb_mixer_interface *mixer)
{
	struct scarlett2_mixer_data *private = mixer->private_data;
	const struct scarlett2_device_info *info = private->info;
	const struct scarlett2_ports *ports = info->ports;
	int num_line_out =
		ports[SCARLETT2_PORT_TYPE_ANALOGUE].num[SCARLETT2_PORT_OUT];
	u8 level_switches[SCARLETT2_LEVEL_SWITCH_MAX];
	u8 pad_switches[SCARLETT2_PAD_SWITCH_MAX];
	struct scarlett2_usb_volume_status volume_status;
	int err, i;

	if (info->level_input_count) {
		err = scarlett2_usb_get_config(
			mixer,
			SCARLETT2_CONFIG_LEVEL_SWITCH,
			info->level_input_count,
			level_switches);
		if (err < 0)
			return err;
		for (i = 0; i < info->level_input_count; i++)
			private->level_switch[i] = level_switches[i];
	}

	if (info->pad_input_count) {
		err = scarlett2_usb_get_config(
			mixer,
			SCARLETT2_CONFIG_PAD_SWITCH,
			info->pad_input_count,
			pad_switches);
		if (err < 0)
			return err;
		for (i = 0; i < info->pad_input_count; i++)
			private->pad_switch[i] = pad_switches[i];
	}

	err = scarlett2_usb_get_volume_status(mixer, &volume_status);
	if (err < 0)
		return err;

	private->master_vol = clamp(
		volume_status.master_vol + SCARLETT2_VOLUME_BIAS,
		0, SCARLETT2_VOLUME_BIAS);

	for (i = 0; i < num_line_out; i++) {
		int volume;

		private->vol_sw_hw_switch[i] =
			info->line_out_hw_vol
				&& volume_status.sw_hw_switch[i];

		volume = private->vol_sw_hw_switch[i]
			   ? volume_status.master_vol
			   : volume_status.sw_vol[i];
		volume = clamp(volume + SCARLETT2_VOLUME_BIAS,
			       0, SCARLETT2_VOLUME_BIAS);
		private->vol[i] = volume;
	}

	for (i = 0; i < info->button_count; i++)
		private->buttons[i] = !!volume_status.buttons[i];

	return 0;
}