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
struct TYPE_2__ {int /*<<< orphan*/  (* enable ) (struct r8152*) ;} ;
struct r8152 {int /*<<< orphan*/  napi; int /*<<< orphan*/  rx_done; int /*<<< orphan*/  intr_urb; int /*<<< orphan*/  control; TYPE_1__ rtl_ops; int /*<<< orphan*/  flags; struct net_device* netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WORK_ENABLE ; 
 int /*<<< orphan*/  _rtl8152_set_rx_mode (struct net_device*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  rtl_start_rx (struct r8152*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct r8152*) ; 
 struct r8152* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8152_post_reset(struct usb_interface *intf)
{
	struct r8152 *tp = usb_get_intfdata(intf);
	struct net_device *netdev;

	if (!tp)
		return 0;

	netdev = tp->netdev;
	if (!netif_running(netdev))
		return 0;

	set_bit(WORK_ENABLE, &tp->flags);
	if (netif_carrier_ok(netdev)) {
		mutex_lock(&tp->control);
		tp->rtl_ops.enable(tp);
		rtl_start_rx(tp);
		_rtl8152_set_rx_mode(netdev);
		mutex_unlock(&tp->control);
	}

	napi_enable(&tp->napi);
	netif_wake_queue(netdev);
	usb_submit_urb(tp->intr_urb, GFP_KERNEL);

	if (!list_empty(&tp->rx_done))
		napi_schedule(&tp->napi);

	return 0;
}