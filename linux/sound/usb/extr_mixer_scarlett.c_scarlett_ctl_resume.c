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
struct usb_mixer_elem_list {int dummy; } ;
struct usb_mixer_elem_info {int channels; int cached; int /*<<< orphan*/ * cache_val; } ;

/* Variables and functions */
 struct usb_mixer_elem_info* mixer_elem_list_to_info (struct usb_mixer_elem_list*) ; 
 int /*<<< orphan*/  snd_usb_set_cur_mix_value (struct usb_mixer_elem_info*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scarlett_ctl_resume(struct usb_mixer_elem_list *list)
{
	struct usb_mixer_elem_info *elem = mixer_elem_list_to_info(list);
	int i;

	for (i = 0; i < elem->channels; i++)
		if (elem->cached & (1 << i))
			snd_usb_set_cur_mix_value(elem, i, i,
						  elem->cache_val[i]);
	return 0;
}