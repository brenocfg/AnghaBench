#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct usb_interface {int dummy; } ;
struct lan78xx_priv {int /*<<< orphan*/  wol; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct lan78xx_net {int /*<<< orphan*/  stat_monitor; int /*<<< orphan*/  flags; int /*<<< orphan*/  net; int /*<<< orphan*/  urb_intr; TYPE_2__ txq; TYPE_2__ txq_pend; int /*<<< orphan*/  suspend_count; scalar_t__* data; } ;
struct TYPE_5__ {int event; } ;
typedef  TYPE_1__ pm_message_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  EVENT_DEV_ASLEEP ; 
 int /*<<< orphan*/  MAC_RX ; 
 int MAC_RX_RXEN_ ; 
 int /*<<< orphan*/  MAC_TX ; 
 int MAC_TX_TXEN_ ; 
 scalar_t__ PMSG_IS_AUTO (TYPE_1__) ; 
 int /*<<< orphan*/  PMT_CTL ; 
 int PMT_CTL_PHY_WAKE_EN_ ; 
 int PMT_CTL_RES_CLR_WKP_EN_ ; 
 int PMT_CTL_RES_CLR_WKP_STS_ ; 
 int PMT_CTL_SUS_MODE_3_ ; 
 int PMT_CTL_SUS_MODE_MASK_ ; 
 int PMT_CTL_WOL_EN_ ; 
 int PMT_CTL_WUPS_MASK_ ; 
 int /*<<< orphan*/  WK_SRC ; 
 int /*<<< orphan*/  WUCSR ; 
 int /*<<< orphan*/  WUCSR2 ; 
 int WUCSR_RFE_WAKE_EN_ ; 
 int WUCSR_STORE_WAKE_ ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int lan78xx_read_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lan78xx_set_suspend (struct lan78xx_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan78xx_terminate_urbs (struct lan78xx_net*) ; 
 int lan78xx_write_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_device_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct lan78xx_net* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lan78xx_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct lan78xx_net *dev = usb_get_intfdata(intf);
	struct lan78xx_priv *pdata = (struct lan78xx_priv *)(dev->data[0]);
	u32 buf;
	int ret;
	int event;

	event = message.event;

	if (!dev->suspend_count++) {
		spin_lock_irq(&dev->txq.lock);
		/* don't autosuspend while transmitting */
		if ((skb_queue_len(&dev->txq) ||
		     skb_queue_len(&dev->txq_pend)) &&
			PMSG_IS_AUTO(message)) {
			spin_unlock_irq(&dev->txq.lock);
			ret = -EBUSY;
			goto out;
		} else {
			set_bit(EVENT_DEV_ASLEEP, &dev->flags);
			spin_unlock_irq(&dev->txq.lock);
		}

		/* stop TX & RX */
		ret = lan78xx_read_reg(dev, MAC_TX, &buf);
		buf &= ~MAC_TX_TXEN_;
		ret = lan78xx_write_reg(dev, MAC_TX, buf);
		ret = lan78xx_read_reg(dev, MAC_RX, &buf);
		buf &= ~MAC_RX_RXEN_;
		ret = lan78xx_write_reg(dev, MAC_RX, buf);

		/* empty out the rx and queues */
		netif_device_detach(dev->net);
		lan78xx_terminate_urbs(dev);
		usb_kill_urb(dev->urb_intr);

		/* reattach */
		netif_device_attach(dev->net);
	}

	if (test_bit(EVENT_DEV_ASLEEP, &dev->flags)) {
		del_timer(&dev->stat_monitor);

		if (PMSG_IS_AUTO(message)) {
			/* auto suspend (selective suspend) */
			ret = lan78xx_read_reg(dev, MAC_TX, &buf);
			buf &= ~MAC_TX_TXEN_;
			ret = lan78xx_write_reg(dev, MAC_TX, buf);
			ret = lan78xx_read_reg(dev, MAC_RX, &buf);
			buf &= ~MAC_RX_RXEN_;
			ret = lan78xx_write_reg(dev, MAC_RX, buf);

			ret = lan78xx_write_reg(dev, WUCSR, 0);
			ret = lan78xx_write_reg(dev, WUCSR2, 0);
			ret = lan78xx_write_reg(dev, WK_SRC, 0xFFF1FF1FUL);

			/* set goodframe wakeup */
			ret = lan78xx_read_reg(dev, WUCSR, &buf);

			buf |= WUCSR_RFE_WAKE_EN_;
			buf |= WUCSR_STORE_WAKE_;

			ret = lan78xx_write_reg(dev, WUCSR, buf);

			ret = lan78xx_read_reg(dev, PMT_CTL, &buf);

			buf &= ~PMT_CTL_RES_CLR_WKP_EN_;
			buf |= PMT_CTL_RES_CLR_WKP_STS_;

			buf |= PMT_CTL_PHY_WAKE_EN_;
			buf |= PMT_CTL_WOL_EN_;
			buf &= ~PMT_CTL_SUS_MODE_MASK_;
			buf |= PMT_CTL_SUS_MODE_3_;

			ret = lan78xx_write_reg(dev, PMT_CTL, buf);

			ret = lan78xx_read_reg(dev, PMT_CTL, &buf);

			buf |= PMT_CTL_WUPS_MASK_;

			ret = lan78xx_write_reg(dev, PMT_CTL, buf);

			ret = lan78xx_read_reg(dev, MAC_RX, &buf);
			buf |= MAC_RX_RXEN_;
			ret = lan78xx_write_reg(dev, MAC_RX, buf);
		} else {
			lan78xx_set_suspend(dev, pdata->wol);
		}
	}

	ret = 0;
out:
	return ret;
}