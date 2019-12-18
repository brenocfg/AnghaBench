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
 int /*<<< orphan*/  SCARLETT2_NUM_METERS ; 
 int scarlett2_add_new_ctl (struct usb_mixer_interface*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scarlett2_meter_ctl ; 

__attribute__((used)) static int scarlett2_add_meter_ctl(struct usb_mixer_interface *mixer)
{
	return scarlett2_add_new_ctl(mixer, &scarlett2_meter_ctl,
				     0, SCARLETT2_NUM_METERS,
				     "Level Meter", NULL);
}