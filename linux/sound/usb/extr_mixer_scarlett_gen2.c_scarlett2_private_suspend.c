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
struct usb_mixer_interface {struct scarlett2_mixer_data* private_data; } ;
struct scarlett2_mixer_data {int /*<<< orphan*/  mixer; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 scalar_t__ cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scarlett2_config_save (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scarlett2_private_suspend(struct usb_mixer_interface *mixer)
{
	struct scarlett2_mixer_data *private = mixer->private_data;

	if (cancel_delayed_work_sync(&private->work))
		scarlett2_config_save(private->mixer);
}