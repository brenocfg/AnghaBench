#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct lan78xx_net {TYPE_1__* net; } ;
struct TYPE_2__ {int /*<<< orphan*/  phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  lan78xx_reset (struct lan78xx_net*) ; 
 int lan78xx_resume (struct usb_interface*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 struct lan78xx_net* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int lan78xx_reset_resume(struct usb_interface *intf)
{
	struct lan78xx_net *dev = usb_get_intfdata(intf);

	lan78xx_reset(dev);

	phy_start(dev->net->phydev);

	return lan78xx_resume(intf);
}