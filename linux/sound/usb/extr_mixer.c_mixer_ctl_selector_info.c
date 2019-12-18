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
struct usb_mixer_elem_info {int /*<<< orphan*/  max; } ;
struct snd_kcontrol {scalar_t__ private_value; struct usb_mixer_elem_info* private_data; } ;
struct snd_ctl_elem_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_ctl_enum_info (struct snd_ctl_elem_info*,int,int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static int mixer_ctl_selector_info(struct snd_kcontrol *kcontrol,
				   struct snd_ctl_elem_info *uinfo)
{
	struct usb_mixer_elem_info *cval = kcontrol->private_data;
	const char **itemlist = (const char **)kcontrol->private_value;

	if (snd_BUG_ON(!itemlist))
		return -EINVAL;
	return snd_ctl_enum_info(uinfo, 1, cval->max, itemlist);
}