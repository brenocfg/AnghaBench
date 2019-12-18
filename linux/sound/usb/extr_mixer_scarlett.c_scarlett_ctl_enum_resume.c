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
struct usb_mixer_elem_info {int /*<<< orphan*/ * cache_val; scalar_t__ cached; } ;

/* Variables and functions */
 struct usb_mixer_elem_info* mixer_elem_list_to_info (struct usb_mixer_elem_list*) ; 
 int /*<<< orphan*/  snd_usb_set_cur_mix_value (struct usb_mixer_elem_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scarlett_ctl_enum_resume(struct usb_mixer_elem_list *list)
{
	struct usb_mixer_elem_info *elem = mixer_elem_list_to_info(list);

	if (elem->cached)
		snd_usb_set_cur_mix_value(elem, 0, 0, *elem->cache_val);
	return 0;
}