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
struct usbmix_name_map {int dummy; } ;
struct usb_mixer_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __build_feature_ctl (struct usb_mixer_interface*,struct usbmix_name_map const*,unsigned int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void build_feature_ctl_badd(struct usb_mixer_interface *mixer,
			      unsigned int ctl_mask, int control, int unitid,
			      const struct usbmix_name_map *badd_map)
{
	__build_feature_ctl(mixer, badd_map, ctl_mask, control,
			NULL, NULL, unitid, 0, 0);
}