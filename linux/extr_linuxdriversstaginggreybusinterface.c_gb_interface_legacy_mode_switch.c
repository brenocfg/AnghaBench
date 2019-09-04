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
struct gb_interface {int disconnected; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gb_interface_deactivate (struct gb_interface*) ; 
 int /*<<< orphan*/  gb_interface_disable (struct gb_interface*) ; 
 int gb_interface_enable (struct gb_interface*) ; 

__attribute__((used)) static int gb_interface_legacy_mode_switch(struct gb_interface *intf)
{
	int ret;

	dev_info(&intf->dev, "legacy mode switch detected\n");

	/* Mark as disconnected to prevent I/O during disable. */
	intf->disconnected = true;
	gb_interface_disable(intf);
	intf->disconnected = false;

	ret = gb_interface_enable(intf);
	if (ret) {
		dev_err(&intf->dev, "failed to re-enable interface: %d\n", ret);
		gb_interface_deactivate(intf);
	}

	return ret;
}