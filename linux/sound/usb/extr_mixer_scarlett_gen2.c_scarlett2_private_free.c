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
struct scarlett2_mixer_data {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct scarlett2_mixer_data*) ; 

__attribute__((used)) static void scarlett2_private_free(struct usb_mixer_interface *mixer)
{
	struct scarlett2_mixer_data *private = mixer->private_data;

	cancel_delayed_work_sync(&private->work);
	kfree(private);
	mixer->private_data = NULL;
}