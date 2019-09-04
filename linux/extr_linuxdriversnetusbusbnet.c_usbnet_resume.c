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
struct TYPE_2__ {scalar_t__ qlen; int /*<<< orphan*/  lock; } ;
struct usbnet {int /*<<< orphan*/  flags; int /*<<< orphan*/  bh; int /*<<< orphan*/  net; TYPE_1__ txq; int /*<<< orphan*/  delay; int /*<<< orphan*/  intf; int /*<<< orphan*/  deferred; int /*<<< orphan*/  suspend_count; } ;
struct usb_interface {int dummy; } ;
struct urb {int /*<<< orphan*/  sg; scalar_t__ context; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_DEVICE_REPORT_IDLE ; 
 int /*<<< orphan*/  EVENT_DEV_ASLEEP ; 
 int /*<<< orphan*/  EVENT_DEV_OPEN ; 
 int /*<<< orphan*/  EVENT_RX_HALT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ TX_QLEN (struct usbnet*) ; 
 int /*<<< orphan*/  __skb_queue_tail (TYPE_1__*,struct sk_buff*) ; 
 int /*<<< orphan*/  __usbnet_status_start_force (struct usbnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_device_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_trans_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_alloc_submit (struct usbnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_autopm_get_interface_no_resume (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface_async (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 struct urb* usb_get_from_anchor (int /*<<< orphan*/ *) ; 
 struct usbnet* usb_get_intfdata (struct usb_interface*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

int usbnet_resume (struct usb_interface *intf)
{
	struct usbnet		*dev = usb_get_intfdata(intf);
	struct sk_buff          *skb;
	struct urb              *res;
	int                     retval;

	if (!--dev->suspend_count) {
		/* resume interrupt URB if it was previously submitted */
		__usbnet_status_start_force(dev, GFP_NOIO);

		spin_lock_irq(&dev->txq.lock);
		while ((res = usb_get_from_anchor(&dev->deferred))) {

			skb = (struct sk_buff *)res->context;
			retval = usb_submit_urb(res, GFP_ATOMIC);
			if (retval < 0) {
				dev_kfree_skb_any(skb);
				kfree(res->sg);
				usb_free_urb(res);
				usb_autopm_put_interface_async(dev->intf);
			} else {
				netif_trans_update(dev->net);
				__skb_queue_tail(&dev->txq, skb);
			}
		}

		smp_mb();
		clear_bit(EVENT_DEV_ASLEEP, &dev->flags);
		spin_unlock_irq(&dev->txq.lock);

		if (test_bit(EVENT_DEV_OPEN, &dev->flags)) {
			/* handle remote wakeup ASAP
			 * we cannot race against stop
			 */
			if (netif_device_present(dev->net) &&
				!timer_pending(&dev->delay) &&
				!test_bit(EVENT_RX_HALT, &dev->flags))
					rx_alloc_submit(dev, GFP_NOIO);

			if (!(dev->txq.qlen >= TX_QLEN(dev)))
				netif_tx_wake_all_queues(dev->net);
			tasklet_schedule (&dev->bh);
		}
	}

	if (test_and_clear_bit(EVENT_DEVICE_REPORT_IDLE, &dev->flags))
		usb_autopm_get_interface_no_resume(intf);

	return 0;
}