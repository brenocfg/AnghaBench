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
struct sk_buff {scalar_t__ len; } ;
struct nci_dev {int /*<<< orphan*/  tx_work; int /*<<< orphan*/  tx_wq; int /*<<< orphan*/  cur_conn_id; int /*<<< orphan*/  tx_q; } ;
struct nci_conn_info {scalar_t__ max_pkt_payload_len; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  NCI_PBF_LAST ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct nci_conn_info* nci_get_conn_info_by_conn_id (struct nci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_push_data_hdr (struct nci_dev*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int nci_queue_tx_data_frags (struct nci_dev*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

int nci_send_data(struct nci_dev *ndev, __u8 conn_id, struct sk_buff *skb)
{
	struct nci_conn_info    *conn_info;
	int rc = 0;

	pr_debug("conn_id 0x%x, plen %d\n", conn_id, skb->len);

	conn_info = nci_get_conn_info_by_conn_id(ndev, conn_id);
	if (!conn_info) {
		rc = -EPROTO;
		goto free_exit;
	}

	/* check if the packet need to be fragmented */
	if (skb->len <= conn_info->max_pkt_payload_len) {
		/* no need to fragment packet */
		nci_push_data_hdr(ndev, conn_id, skb, NCI_PBF_LAST);

		skb_queue_tail(&ndev->tx_q, skb);
	} else {
		/* fragment packet and queue the fragments */
		rc = nci_queue_tx_data_frags(ndev, conn_id, skb);
		if (rc) {
			pr_err("failed to fragment tx data packet\n");
			goto free_exit;
		}
	}

	ndev->cur_conn_id = conn_id;
	queue_work(ndev->tx_wq, &ndev->tx_work);

	goto exit;

free_exit:
	kfree_skb(skb);

exit:
	return rc;
}