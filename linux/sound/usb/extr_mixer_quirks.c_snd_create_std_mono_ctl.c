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
typedef  int /*<<< orphan*/  snd_kcontrol_tlv_rw_t ;

/* Variables and functions */
 int snd_create_std_mono_ctl_offset (struct usb_mixer_interface*,unsigned int,unsigned int,unsigned int,int,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_create_std_mono_ctl(struct usb_mixer_interface *mixer,
				unsigned int unitid,
				unsigned int control,
				unsigned int cmask,
				int val_type,
				const char *name,
				snd_kcontrol_tlv_rw_t *tlv_callback)
{
	return snd_create_std_mono_ctl_offset(mixer, unitid, control, cmask,
		val_type, 0 /* Offset */, name, tlv_callback);
}