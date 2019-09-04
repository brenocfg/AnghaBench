#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct nfc_dev {scalar_t__ rf_mode; int /*<<< orphan*/  dev; TYPE_1__* ops; int /*<<< orphan*/  check_pres_timer; int /*<<< orphan*/  shutting_down; TYPE_2__* active_target; } ;
typedef  int /*<<< orphan*/  data_exchange_cb_t ;
struct TYPE_4__ {scalar_t__ idx; } ;
struct TYPE_3__ {int (* im_transceive ) (struct nfc_dev*,TYPE_2__*,struct sk_buff*,int /*<<< orphan*/ ,void*) ;int (* tm_send ) (struct nfc_dev*,struct sk_buff*) ;scalar_t__ check_presence; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int ENODEV ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  NFC_CHECK_PRES_FREQ_MS ; 
 scalar_t__ NFC_RF_INITIATOR ; 
 scalar_t__ NFC_RF_TARGET ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int stub1 (struct nfc_dev*,TYPE_2__*,struct sk_buff*,int /*<<< orphan*/ ,void*) ; 
 int stub2 (struct nfc_dev*,struct sk_buff*) ; 

int nfc_data_exchange(struct nfc_dev *dev, u32 target_idx, struct sk_buff *skb,
		      data_exchange_cb_t cb, void *cb_context)
{
	int rc;

	pr_debug("dev_name=%s target_idx=%u skb->len=%u\n",
		 dev_name(&dev->dev), target_idx, skb->len);

	device_lock(&dev->dev);

	if (!device_is_registered(&dev->dev)) {
		rc = -ENODEV;
		kfree_skb(skb);
		goto error;
	}

	if (dev->rf_mode == NFC_RF_INITIATOR && dev->active_target != NULL) {
		if (dev->active_target->idx != target_idx) {
			rc = -EADDRNOTAVAIL;
			kfree_skb(skb);
			goto error;
		}

		if (dev->ops->check_presence)
			del_timer_sync(&dev->check_pres_timer);

		rc = dev->ops->im_transceive(dev, dev->active_target, skb, cb,
					     cb_context);

		if (!rc && dev->ops->check_presence && !dev->shutting_down)
			mod_timer(&dev->check_pres_timer, jiffies +
				  msecs_to_jiffies(NFC_CHECK_PRES_FREQ_MS));
	} else if (dev->rf_mode == NFC_RF_TARGET && dev->ops->tm_send != NULL) {
		rc = dev->ops->tm_send(dev, skb);
	} else {
		rc = -ENOTCONN;
		kfree_skb(skb);
		goto error;
	}


error:
	device_unlock(&dev->dev);
	return rc;
}