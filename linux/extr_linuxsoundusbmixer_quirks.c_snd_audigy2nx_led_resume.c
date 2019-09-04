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
struct usb_mixer_elem_list {int /*<<< orphan*/  mixer; TYPE_1__* kctl; } ;
struct TYPE_2__ {int private_value; } ;

/* Variables and functions */
 int snd_audigy2nx_led_update (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int snd_audigy2nx_led_resume(struct usb_mixer_elem_list *list)
{
	int priv_value = list->kctl->private_value;

	return snd_audigy2nx_led_update(list->mixer, priv_value >> 8,
					priv_value & 0xff);
}