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
struct usb_mixer_elem_list {int id; int /*<<< orphan*/  dump; struct usb_mixer_interface* mixer; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_usb_mixer_dump_cval ; 

void snd_usb_mixer_elem_init_std(struct usb_mixer_elem_list *list,
				 struct usb_mixer_interface *mixer,
				 int unitid)
{
	list->mixer = mixer;
	list->id = unitid;
	list->dump = snd_usb_mixer_dump_cval;
#ifdef CONFIG_PM
	list->resume = restore_mixer_value;
#endif
}