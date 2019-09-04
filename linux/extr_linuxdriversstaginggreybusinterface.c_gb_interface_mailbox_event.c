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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct gb_interface {int quirks; int /*<<< orphan*/  mutex; int /*<<< orphan*/  mode_switch_completion; int /*<<< orphan*/  dev; int /*<<< orphan*/  mode_switch; } ;

/* Variables and functions */
 int GB_INTERFACE_QUIRK_LEGACY_MODE_SWITCH ; 
 int /*<<< orphan*/  GB_SVC_INTF_MAILBOX_GREYBUS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_interface_deactivate (struct gb_interface*) ; 
 int /*<<< orphan*/  gb_interface_disable (struct gb_interface*) ; 
 int /*<<< orphan*/  gb_interface_legacy_mode_switch (struct gb_interface*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void gb_interface_mailbox_event(struct gb_interface *intf, u16 result,
				u32 mailbox)
{
	mutex_lock(&intf->mutex);

	if (result) {
		dev_warn(&intf->dev,
			 "mailbox event with UniPro error: 0x%04x\n",
			 result);
		goto err_disable;
	}

	if (mailbox != GB_SVC_INTF_MAILBOX_GREYBUS) {
		dev_warn(&intf->dev,
			 "mailbox event with unexpected value: 0x%08x\n",
			 mailbox);
		goto err_disable;
	}

	if (intf->quirks & GB_INTERFACE_QUIRK_LEGACY_MODE_SWITCH) {
		gb_interface_legacy_mode_switch(intf);
		goto out_unlock;
	}

	if (!intf->mode_switch) {
		dev_warn(&intf->dev, "unexpected mailbox event: 0x%08x\n",
			 mailbox);
		goto err_disable;
	}

	dev_info(&intf->dev, "mode switch detected\n");

	complete(&intf->mode_switch_completion);

out_unlock:
	mutex_unlock(&intf->mutex);

	return;

err_disable:
	gb_interface_disable(intf);
	gb_interface_deactivate(intf);
	mutex_unlock(&intf->mutex);
}