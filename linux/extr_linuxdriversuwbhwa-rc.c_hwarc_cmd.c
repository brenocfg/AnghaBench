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
struct uwb_rccb {int dummy; } ;
struct uwb_rc {struct hwarc* priv; } ;
struct hwarc {TYPE_3__* usb_iface; int /*<<< orphan*/  usb_dev; } ;
struct TYPE_6__ {TYPE_2__* cur_altsetting; } ;
struct TYPE_4__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 int /*<<< orphan*/  WA_EXEC_RC_CMD ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int hwarc_cmd(struct uwb_rc *uwb_rc, const struct uwb_rccb *cmd, size_t cmd_size)
{
	struct hwarc *hwarc = uwb_rc->priv;
	return usb_control_msg(
		hwarc->usb_dev, usb_sndctrlpipe(hwarc->usb_dev, 0),
		WA_EXEC_RC_CMD, USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
		0, hwarc->usb_iface->cur_altsetting->desc.bInterfaceNumber,
		(void *) cmd, cmd_size, 100 /* FIXME: this is totally arbitrary */);
}