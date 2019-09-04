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
struct TYPE_2__ {int /*<<< orphan*/  req; } ;
struct f_uas {int flags; TYPE_1__ cmd; int /*<<< orphan*/  ep_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int USBG_BOT_CMD_PEND ; 
 int usb_ep_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bot_enqueue_cmd_cbw(struct f_uas *fu)
{
	int ret;

	if (fu->flags & USBG_BOT_CMD_PEND)
		return 0;

	ret = usb_ep_queue(fu->ep_out, fu->cmd.req, GFP_ATOMIC);
	if (!ret)
		fu->flags |= USBG_BOT_CMD_PEND;
	return ret;
}