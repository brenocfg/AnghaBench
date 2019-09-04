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
struct sk_buff {int dummy; } ;
struct mwifiex_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MWIFIEX_USB_EP_CMD_EVENT ; 
 int /*<<< orphan*/  mwifiex_submit_rx_urb (struct mwifiex_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_usb_cmd_event_complete(struct mwifiex_adapter *adapter,
				       struct sk_buff *skb)
{
	mwifiex_submit_rx_urb(adapter, MWIFIEX_USB_EP_CMD_EVENT);

	return 0;
}