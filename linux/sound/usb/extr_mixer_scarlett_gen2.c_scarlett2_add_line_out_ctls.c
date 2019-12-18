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
struct usb_mixer_interface {struct scarlett2_mixer_data* private_data; } ;
struct scarlett2_ports {int* num; } ;
struct scarlett2_mixer_data {TYPE_2__** button_ctls; struct scarlett2_device_info* info; TYPE_2__** vol_ctls; scalar_t__* vol_sw_hw_switch; TYPE_2__* master_vol_ctl; } ;
struct scarlett2_device_info {char** line_out_descrs; int button_count; scalar_t__ line_out_hw_vol; struct scarlett2_ports* ports; } ;
typedef  int /*<<< orphan*/  s ;
struct TYPE_4__ {TYPE_1__* vd; } ;
struct TYPE_3__ {int /*<<< orphan*/  access; } ;

/* Variables and functions */
 size_t SCARLETT2_PORT_OUT ; 
 size_t SCARLETT2_PORT_TYPE_ANALOGUE ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_WRITE ; 
 int SNDRV_CTL_ELEM_ID_NAME_MAXLEN ; 
 int scarlett2_add_new_ctl (struct usb_mixer_interface*,int /*<<< orphan*/ *,int,int,char*,TYPE_2__**) ; 
 int /*<<< orphan*/  scarlett2_button_ctl ; 
 char** scarlett2_button_names ; 
 int /*<<< orphan*/  scarlett2_line_out_volume_ctl ; 
 int /*<<< orphan*/  scarlett2_master_volume_ctl ; 
 int /*<<< orphan*/  scarlett2_sw_hw_enum_ctl ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int scarlett2_add_line_out_ctls(struct usb_mixer_interface *mixer)
{
	struct scarlett2_mixer_data *private = mixer->private_data;
	const struct scarlett2_device_info *info = private->info;
	const struct scarlett2_ports *ports = info->ports;
	int num_line_out =
		ports[SCARLETT2_PORT_TYPE_ANALOGUE].num[SCARLETT2_PORT_OUT];
	int err, i;
	char s[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];

	/* Add R/O HW volume control */
	if (info->line_out_hw_vol) {
		snprintf(s, sizeof(s), "Master HW Playback Volume");
		err = scarlett2_add_new_ctl(mixer,
					    &scarlett2_master_volume_ctl,
					    0, 1, s, &private->master_vol_ctl);
		if (err < 0)
			return err;
	}

	/* Add volume controls */
	for (i = 0; i < num_line_out; i++) {

		/* Fader */
		if (info->line_out_descrs[i])
			snprintf(s, sizeof(s),
				 "Line %02d (%s) Playback Volume",
				 i + 1, info->line_out_descrs[i]);
		else
			snprintf(s, sizeof(s),
				 "Line %02d Playback Volume",
				 i + 1);
		err = scarlett2_add_new_ctl(mixer,
					    &scarlett2_line_out_volume_ctl,
					    i, 1, s, &private->vol_ctls[i]);
		if (err < 0)
			return err;

		/* Make the fader read-only if the SW/HW switch is set to HW */
		if (private->vol_sw_hw_switch[i])
			private->vol_ctls[i]->vd[0].access &=
				~SNDRV_CTL_ELEM_ACCESS_WRITE;

		/* SW/HW Switch */
		if (info->line_out_hw_vol) {
			snprintf(s, sizeof(s),
				 "Line Out %02d Volume Control Playback Enum",
				 i + 1);
			err = scarlett2_add_new_ctl(mixer,
						    &scarlett2_sw_hw_enum_ctl,
						    i, 1, s, NULL);
			if (err < 0)
				return err;
		}
	}

	/* Add HW button controls */
	for (i = 0; i < private->info->button_count; i++) {
		err = scarlett2_add_new_ctl(mixer, &scarlett2_button_ctl,
					    i, 1, scarlett2_button_names[i],
					    &private->button_ctls[i]);
		if (err < 0)
			return err;
	}

	return 0;
}