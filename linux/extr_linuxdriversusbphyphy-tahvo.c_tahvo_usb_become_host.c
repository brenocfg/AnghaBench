#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* otg; } ;
struct tahvo_usb {TYPE_4__ phy; int /*<<< orphan*/  extcon; TYPE_2__* pt_dev; } ;
struct retu_dev {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  state; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTCON_USB_HOST ; 
 int /*<<< orphan*/  OTG_STATE_A_IDLE ; 
 int /*<<< orphan*/  TAHVO_REG_USBR ; 
 int USBR_MASTER_SW1 ; 
 int USBR_MASTER_SW2 ; 
 int USBR_NSUSPEND ; 
 int USBR_REGOUT ; 
 int /*<<< orphan*/  check_vbus_state (struct tahvo_usb*) ; 
 struct retu_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extcon_set_state_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  retu_write (struct retu_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tahvo_usb_become_host(struct tahvo_usb *tu)
{
	struct retu_dev *rdev = dev_get_drvdata(tu->pt_dev->dev.parent);

	extcon_set_state_sync(tu->extcon, EXTCON_USB_HOST, true);

	/* Power up the transceiver in USB host mode */
	retu_write(rdev, TAHVO_REG_USBR, USBR_REGOUT | USBR_NSUSPEND |
		   USBR_MASTER_SW2 | USBR_MASTER_SW1);
	tu->phy.otg->state = OTG_STATE_A_IDLE;

	check_vbus_state(tu);
}