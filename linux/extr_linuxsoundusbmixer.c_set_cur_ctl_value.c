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
struct usb_mixer_elem_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UAC_SET_CUR ; 
 int snd_usb_mixer_set_ctl_value (struct usb_mixer_elem_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int set_cur_ctl_value(struct usb_mixer_elem_info *cval,
			     int validx, int value)
{
	return snd_usb_mixer_set_ctl_value(cval, UAC_SET_CUR, validx, value);
}