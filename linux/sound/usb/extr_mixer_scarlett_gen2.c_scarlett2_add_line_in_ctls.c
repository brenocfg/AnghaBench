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
struct usb_mixer_interface {struct scarlett2_mixer_data* private_data; } ;
struct scarlett2_mixer_data {struct scarlett2_device_info* info; } ;
struct scarlett2_device_info {int level_input_count; int pad_input_count; } ;
typedef  int /*<<< orphan*/  s ;

/* Variables and functions */
 int SNDRV_CTL_ELEM_ID_NAME_MAXLEN ; 
 int scarlett2_add_new_ctl (struct usb_mixer_interface*,int /*<<< orphan*/ *,int,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scarlett2_level_enum_ctl ; 
 int /*<<< orphan*/  scarlett2_pad_ctl ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int scarlett2_add_line_in_ctls(struct usb_mixer_interface *mixer)
{
	struct scarlett2_mixer_data *private = mixer->private_data;
	const struct scarlett2_device_info *info = private->info;
	int err, i;
	char s[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];

	/* Add input level (line/inst) controls */
	for (i = 0; i < info->level_input_count; i++) {
		snprintf(s, sizeof(s), "Line In %d Level Capture Enum", i + 1);
		err = scarlett2_add_new_ctl(mixer, &scarlett2_level_enum_ctl,
					    i, 1, s, NULL);
		if (err < 0)
			return err;
	}

	/* Add input pad controls */
	for (i = 0; i < info->pad_input_count; i++) {
		snprintf(s, sizeof(s), "Line In %d Pad Capture Switch", i + 1);
		err = scarlett2_add_new_ctl(mixer, &scarlett2_pad_ctl,
					    i, 1, s, NULL);
		if (err < 0)
			return err;
	}

	return 0;
}