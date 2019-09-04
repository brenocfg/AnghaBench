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
struct urb {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  dev; } ;
struct rtl_usb {int /*<<< orphan*/  rx_cleanup_urbs; int /*<<< orphan*/  rx_queue; int /*<<< orphan*/  rx_work_tasklet; int /*<<< orphan*/  rx_submitted; } ;
struct TYPE_4__ {int /*<<< orphan*/  rtl_wq; int /*<<< orphan*/  lps_change_work; int /*<<< orphan*/  fill_h2c_cmd; } ;
struct rtl_priv {TYPE_3__* cfg; TYPE_1__ works; } ;
struct rtl_hal {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* hw_disable ) (struct ieee80211_hw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SET_USB_STOP (struct rtl_usb*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_usb* rtl_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_usbpriv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  set_hal_stop (struct rtl_hal*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 struct urb* usb_get_from_anchor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtl_usb_stop(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));
	struct urb *urb;

	/* should after adapter start and interrupt enable. */
	set_hal_stop(rtlhal);
	cancel_work_sync(&rtlpriv->works.fill_h2c_cmd);
	/* Enable software */
	SET_USB_STOP(rtlusb);

	/* free pre-allocated URBs from rtl_usb_start() */
	usb_kill_anchored_urbs(&rtlusb->rx_submitted);

	tasklet_kill(&rtlusb->rx_work_tasklet);
	cancel_work_sync(&rtlpriv->works.lps_change_work);

	flush_workqueue(rtlpriv->works.rtl_wq);

	skb_queue_purge(&rtlusb->rx_queue);

	while ((urb = usb_get_from_anchor(&rtlusb->rx_cleanup_urbs))) {
		usb_free_coherent(urb->dev, urb->transfer_buffer_length,
				urb->transfer_buffer, urb->transfer_dma);
		usb_free_urb(urb);
	}

	rtlpriv->cfg->ops->hw_disable(hw);
}