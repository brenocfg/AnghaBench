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
struct scarlett_device_info {int /*<<< orphan*/  opt_master; } ;
typedef  int /*<<< orphan*/  mx ;

/* Variables and functions */
 int SNDRV_CTL_ELEM_ID_NAME_MAXLEN ; 
 int /*<<< orphan*/  USB_MIXER_S16 ; 
 int add_new_ctl (struct usb_mixer_interface*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *,struct usb_mixer_elem_info**) ; 
 int /*<<< orphan*/  scarlett_ctl_enum_resume ; 
 int /*<<< orphan*/  scarlett_ctl_resume ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char const*) ; 
 int /*<<< orphan*/  usb_scarlett_ctl_dynamic_enum ; 
 int /*<<< orphan*/  usb_scarlett_ctl_master ; 
 int /*<<< orphan*/  usb_scarlett_ctl_switch ; 

__attribute__((used)) static int add_output_ctls(struct usb_mixer_interface *mixer,
			   int index, const char *name,
			   const struct scarlett_device_info *info)
{
	int err;
	char mx[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	struct usb_mixer_elem_info *elem;

	/* Add mute switch */
	snprintf(mx, sizeof(mx), "Master %d (%s) Playback Switch",
		index + 1, name);
	err = add_new_ctl(mixer, &usb_scarlett_ctl_switch,
			  scarlett_ctl_resume, 0x0a, 0x01,
			  2*index+1, USB_MIXER_S16, 2, mx, NULL, &elem);
	if (err < 0)
		return err;

	/* Add volume control and initialize to 0 */
	snprintf(mx, sizeof(mx), "Master %d (%s) Playback Volume",
		index + 1, name);
	err = add_new_ctl(mixer, &usb_scarlett_ctl_master,
			  scarlett_ctl_resume, 0x0a, 0x02,
			  2*index+1, USB_MIXER_S16, 2, mx, NULL, &elem);
	if (err < 0)
		return err;

	/* Add L channel source playback enumeration */
	snprintf(mx, sizeof(mx), "Master %dL (%s) Source Playback Enum",
		index + 1, name);
	err = add_new_ctl(mixer, &usb_scarlett_ctl_dynamic_enum,
			  scarlett_ctl_enum_resume, 0x33, 0x00,
			  2*index, USB_MIXER_S16, 1, mx, &info->opt_master,
			  &elem);
	if (err < 0)
		return err;

	/* Add R channel source playback enumeration */
	snprintf(mx, sizeof(mx), "Master %dR (%s) Source Playback Enum",
		index + 1, name);
	err = add_new_ctl(mixer, &usb_scarlett_ctl_dynamic_enum,
			  scarlett_ctl_enum_resume, 0x33, 0x00,
			  2*index+1, USB_MIXER_S16, 1, mx, &info->opt_master,
			  &elem);
	if (err < 0)
		return err;

	return 0;
}