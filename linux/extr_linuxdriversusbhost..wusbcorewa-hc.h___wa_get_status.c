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
struct wahc {scalar_t__ status; TYPE_3__* usb_iface; int /*<<< orphan*/  usb_dev; } ;
typedef  scalar_t__ s32 ;
struct TYPE_6__ {TYPE_2__* cur_altsetting; } ;
struct TYPE_4__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_CTRL_GET_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int /*<<< orphan*/  USB_REQ_GET_STATUS ; 
 int USB_TYPE_CLASS ; 
 scalar_t__ usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
s32 __wa_get_status(struct wahc *wa)
{
	s32 result;
	result = usb_control_msg(
		wa->usb_dev, usb_rcvctrlpipe(wa->usb_dev, 0),
		USB_REQ_GET_STATUS,
		USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
		0, wa->usb_iface->cur_altsetting->desc.bInterfaceNumber,
		&wa->status, sizeof(wa->status), USB_CTRL_GET_TIMEOUT);
	if (result >= 0)
		result = wa->status;
	return result;
}