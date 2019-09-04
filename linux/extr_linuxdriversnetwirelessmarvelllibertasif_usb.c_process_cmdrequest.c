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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t u8 ;
struct sk_buff {int dummy; } ;
struct lbs_private {scalar_t__ resp_idx; int* resp_len; int /*<<< orphan*/  driver_lock; int /*<<< orphan*/ * resp_buf; } ;
struct if_usb_card {TYPE_1__* udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int LBS_CMD_BUFFER_SIZE ; 
 int MESSAGE_HEADER_LEN ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lbs_deb_usbd (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lbs_notify_command_response (struct lbs_private*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void process_cmdrequest(int recvlength, uint8_t *recvbuff,
				      struct sk_buff *skb,
				      struct if_usb_card *cardp,
				      struct lbs_private *priv)
{
	unsigned long flags;
	u8 i;

	if (recvlength > LBS_CMD_BUFFER_SIZE) {
		lbs_deb_usbd(&cardp->udev->dev,
			     "The receive buffer is too large\n");
		kfree_skb(skb);
		return;
	}

	spin_lock_irqsave(&priv->driver_lock, flags);

	i = (priv->resp_idx == 0) ? 1 : 0;
	BUG_ON(priv->resp_len[i]);
	priv->resp_len[i] = (recvlength - MESSAGE_HEADER_LEN);
	memcpy(priv->resp_buf[i], recvbuff + MESSAGE_HEADER_LEN,
		priv->resp_len[i]);
	kfree_skb(skb);
	lbs_notify_command_response(priv, i);

	spin_unlock_irqrestore(&priv->driver_lock, flags);

	lbs_deb_usbd(&cardp->udev->dev,
		    "Wake up main thread to handle cmd response\n");
}