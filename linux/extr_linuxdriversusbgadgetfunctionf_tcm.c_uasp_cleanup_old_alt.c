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
struct f_uas {int flags; int /*<<< orphan*/ * stream; int /*<<< orphan*/  ep_cmd; int /*<<< orphan*/  ep_status; int /*<<< orphan*/  ep_out; int /*<<< orphan*/  ep_in; } ;

/* Variables and functions */
 int UASP_SS_EP_COMP_NUM_STREAMS ; 
 int USBG_ENABLED ; 
 int /*<<< orphan*/  uasp_cleanup_one_stream (struct f_uas*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uasp_free_cmdreq (struct f_uas*) ; 
 int /*<<< orphan*/  usb_ep_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uasp_cleanup_old_alt(struct f_uas *fu)
{
	int i;

	if (!(fu->flags & USBG_ENABLED))
		return;

	usb_ep_disable(fu->ep_in);
	usb_ep_disable(fu->ep_out);
	usb_ep_disable(fu->ep_status);
	usb_ep_disable(fu->ep_cmd);

	for (i = 0; i < UASP_SS_EP_COMP_NUM_STREAMS; i++)
		uasp_cleanup_one_stream(fu, &fu->stream[i]);
	uasp_free_cmdreq(fu);
}