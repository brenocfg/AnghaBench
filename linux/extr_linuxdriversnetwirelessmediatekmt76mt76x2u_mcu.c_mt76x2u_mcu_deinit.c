#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  urb; } ;
struct TYPE_5__ {TYPE_3__ res; } ;
struct mt76_usb {TYPE_2__ mcu; } ;
struct TYPE_4__ {struct mt76_usb usb; } ;
struct mt76x2_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt76u_buf_free (TYPE_3__*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

void mt76x2u_mcu_deinit(struct mt76x2_dev *dev)
{
	struct mt76_usb *usb = &dev->mt76.usb;

	usb_kill_urb(usb->mcu.res.urb);
	mt76u_buf_free(&usb->mcu.res);
}