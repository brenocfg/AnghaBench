#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_mixer_elem_list {TYPE_1__* kctl; int /*<<< orphan*/  mixer; } ;
struct TYPE_2__ {int /*<<< orphan*/  private_value; } ;

/* Variables and functions */
 int snd_soundblaster_e1_switch_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_soundblaster_e1_switch_resume(struct usb_mixer_elem_list *list)
{
	return snd_soundblaster_e1_switch_update(list->mixer,
						 list->kctl->private_value);
}