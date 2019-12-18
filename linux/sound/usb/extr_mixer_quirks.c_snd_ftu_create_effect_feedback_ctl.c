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

/* Variables and functions */
 int USB_MIXER_U8 ; 
 int snd_create_std_mono_ctl (struct usb_mixer_interface*,unsigned int const,unsigned int const,unsigned int const,int const,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ftu_create_effect_feedback_ctl(struct usb_mixer_interface *mixer)
{
	static const char name[] = "Effect Feedback Volume";
	const unsigned int id = 6;
	const int val_type = USB_MIXER_U8;
	const unsigned int control = 4;
	const unsigned int cmask = 0;

	return snd_create_std_mono_ctl(mixer, id, control, cmask, val_type,
					name, NULL);
}