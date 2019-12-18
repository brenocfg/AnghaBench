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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct nci_dev {int /*<<< orphan*/  flags; int /*<<< orphan*/  data_timer; } ;
struct nci_conn_info {void* data_exchange_cb_context; int /*<<< orphan*/  (* data_exchange_cb ) (void*,struct sk_buff*,int) ;} ;
typedef  int /*<<< orphan*/  (* data_exchange_cb_t ) (void*,struct sk_buff*,int) ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_DATA_EXCHANGE ; 
 int /*<<< orphan*/  NCI_DATA_EXCHANGE_TO ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct nci_conn_info* nci_get_conn_info_by_conn_id (struct nci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

void nci_data_exchange_complete(struct nci_dev *ndev, struct sk_buff *skb,
				__u8 conn_id, int err)
{
	struct nci_conn_info    *conn_info;
	data_exchange_cb_t cb;
	void *cb_context;

	conn_info = nci_get_conn_info_by_conn_id(ndev, conn_id);
	if (!conn_info) {
		kfree_skb(skb);
		goto exit;
	}

	cb = conn_info->data_exchange_cb;
	cb_context = conn_info->data_exchange_cb_context;

	pr_debug("len %d, err %d\n", skb ? skb->len : 0, err);

	/* data exchange is complete, stop the data timer */
	del_timer_sync(&ndev->data_timer);
	clear_bit(NCI_DATA_EXCHANGE_TO, &ndev->flags);

	if (cb) {
		/* forward skb to nfc core */
		cb(cb_context, skb, err);
	} else if (skb) {
		pr_err("no rx callback, dropping rx data...\n");

		/* no waiting callback, free skb */
		kfree_skb(skb);
	}

exit:
	clear_bit(NCI_DATA_EXCHANGE, &ndev->flags);
}