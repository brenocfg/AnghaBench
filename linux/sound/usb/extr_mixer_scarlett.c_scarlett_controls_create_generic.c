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
struct usb_mixer_interface {int dummy; } ;
struct usb_mixer_elem_info {int dummy; } ;
struct scarlett_mixer_control {int type; int num; int /*<<< orphan*/  name; } ;
struct scarlett_device_info {int num_controls; struct scarlett_mixer_control* controls; } ;

/* Variables and functions */
#define  SCARLETT_OUTPUTS 130 
#define  SCARLETT_SWITCH_IMPEDANCE 129 
#define  SCARLETT_SWITCH_PAD 128 
 int SNDRV_CTL_ELEM_ID_NAME_MAXLEN ; 
 int /*<<< orphan*/  USB_MIXER_S16 ; 
 int add_new_ctl (struct usb_mixer_interface*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *,struct usb_mixer_elem_info**) ; 
 int add_output_ctls (struct usb_mixer_interface*,int,int /*<<< orphan*/ ,struct scarlett_device_info*) ; 
 int /*<<< orphan*/  opt_impedance ; 
 int /*<<< orphan*/  opt_pad ; 
 int /*<<< orphan*/  scarlett_ctl_enum_resume ; 
 int /*<<< orphan*/  scarlett_ctl_resume ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  usb_scarlett_ctl_enum ; 
 int /*<<< orphan*/  usb_scarlett_ctl_master ; 
 int /*<<< orphan*/  usb_scarlett_ctl_switch ; 

__attribute__((used)) static int scarlett_controls_create_generic(struct usb_mixer_interface *mixer,
	struct scarlett_device_info *info)
{
	int i, err;
	char mx[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	const struct scarlett_mixer_control *ctl;
	struct usb_mixer_elem_info *elem;

	/* create master switch and playback volume */
	err = add_new_ctl(mixer, &usb_scarlett_ctl_switch,
			  scarlett_ctl_resume, 0x0a, 0x01, 0,
			  USB_MIXER_S16, 1, "Master Playback Switch", NULL,
			  &elem);
	if (err < 0)
		return err;

	err = add_new_ctl(mixer, &usb_scarlett_ctl_master,
			  scarlett_ctl_resume, 0x0a, 0x02, 0,
			  USB_MIXER_S16, 1, "Master Playback Volume", NULL,
			  &elem);
	if (err < 0)
		return err;

	/* iterate through controls in info struct and create each one */
	for (i = 0; i < info->num_controls; i++) {
		ctl = &info->controls[i];

		switch (ctl->type) {
		case SCARLETT_OUTPUTS:
			err = add_output_ctls(mixer, ctl->num, ctl->name, info);
			if (err < 0)
				return err;
			break;
		case SCARLETT_SWITCH_IMPEDANCE:
			sprintf(mx, "Input %d Impedance Switch", ctl->num);
			err = add_new_ctl(mixer, &usb_scarlett_ctl_enum,
					  scarlett_ctl_enum_resume, 0x01,
					  0x09, ctl->num, USB_MIXER_S16, 1, mx,
					  &opt_impedance, &elem);
			if (err < 0)
				return err;
			break;
		case SCARLETT_SWITCH_PAD:
			sprintf(mx, "Input %d Pad Switch", ctl->num);
			err = add_new_ctl(mixer, &usb_scarlett_ctl_enum,
					  scarlett_ctl_enum_resume, 0x01,
					  0x0b, ctl->num, USB_MIXER_S16, 1, mx,
					  &opt_pad, &elem);
			if (err < 0)
				return err;
			break;
		}
	}

	return 0;
}