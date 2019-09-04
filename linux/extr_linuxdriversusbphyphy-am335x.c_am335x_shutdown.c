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
struct usb_phy {int /*<<< orphan*/  dev; } ;
struct am335x_phy {int /*<<< orphan*/  dr_mode; int /*<<< orphan*/  id; int /*<<< orphan*/  phy_ctrl; } ;

/* Variables and functions */
 struct am335x_phy* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_ctrl_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void am335x_shutdown(struct usb_phy *phy)
{
	struct am335x_phy *am_phy = dev_get_drvdata(phy->dev);

	phy_ctrl_power(am_phy->phy_ctrl, am_phy->id, am_phy->dr_mode, false);
}