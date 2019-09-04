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
struct tx_buf {struct tx_buf* buf; int /*<<< orphan*/  list; int /*<<< orphan*/  skb_queue; struct hif_device_usb* hif_dev; int /*<<< orphan*/  urb; } ;
struct TYPE_2__ {int tx_buf_cnt; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  tx_skb_queue; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  tx_pending; } ;
struct hif_device_usb {TYPE_1__ tx; int /*<<< orphan*/  mgmt_submitted; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MAX_TX_BUF_SIZE ; 
 int MAX_TX_URB_NUM ; 
 int /*<<< orphan*/  __skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_hif_usb_dealloc_tx_urbs (struct hif_device_usb*) ; 
 int /*<<< orphan*/  init_usb_anchor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tx_buf*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath9k_hif_usb_alloc_tx_urbs(struct hif_device_usb *hif_dev)
{
	struct tx_buf *tx_buf;
	int i;

	INIT_LIST_HEAD(&hif_dev->tx.tx_buf);
	INIT_LIST_HEAD(&hif_dev->tx.tx_pending);
	spin_lock_init(&hif_dev->tx.tx_lock);
	__skb_queue_head_init(&hif_dev->tx.tx_skb_queue);
	init_usb_anchor(&hif_dev->mgmt_submitted);

	for (i = 0; i < MAX_TX_URB_NUM; i++) {
		tx_buf = kzalloc(sizeof(struct tx_buf), GFP_KERNEL);
		if (!tx_buf)
			goto err;

		tx_buf->buf = kzalloc(MAX_TX_BUF_SIZE, GFP_KERNEL);
		if (!tx_buf->buf)
			goto err;

		tx_buf->urb = usb_alloc_urb(0, GFP_KERNEL);
		if (!tx_buf->urb)
			goto err;

		tx_buf->hif_dev = hif_dev;
		__skb_queue_head_init(&tx_buf->skb_queue);

		list_add_tail(&tx_buf->list, &hif_dev->tx.tx_buf);
	}

	hif_dev->tx.tx_buf_cnt = MAX_TX_URB_NUM;

	return 0;
err:
	if (tx_buf) {
		kfree(tx_buf->buf);
		kfree(tx_buf);
	}
	ath9k_hif_usb_dealloc_tx_urbs(hif_dev);
	return -ENOMEM;
}