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
struct nci_loopback_data {int conn_id; struct sk_buff* data; } ;
struct nci_dev {int cur_conn_id; } ;
struct nci_conn_info {struct sk_buff* rx_skb; struct nci_dev* data_exchange_cb_context; int /*<<< orphan*/  data_exchange_cb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROTO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NCI_DATA_HDR_SIZE ; 
 int /*<<< orphan*/  NCI_DATA_TIMEOUT ; 
 int /*<<< orphan*/  NCI_DESTINATION_NFCC_LOOPBACK ; 
 int NCI_STATUS_OK ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int nci_core_conn_create (struct nci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nci_conn_info* nci_get_conn_info_by_conn_id (struct nci_dev*,int) ; 
 int nci_get_conn_info_by_dest_type_params (struct nci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nci_nfcc_loopback_cb ; 
 int nci_request (struct nci_dev*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_send_data_req ; 
 struct sk_buff* nci_skb_alloc (struct nci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,void*,size_t) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

int nci_nfcc_loopback(struct nci_dev *ndev, void *data, size_t data_len,
		      struct sk_buff **resp)
{
	int r;
	struct nci_loopback_data loopback_data;
	struct nci_conn_info *conn_info;
	struct sk_buff *skb;
	int conn_id = nci_get_conn_info_by_dest_type_params(ndev,
					NCI_DESTINATION_NFCC_LOOPBACK, NULL);

	if (conn_id < 0) {
		r = nci_core_conn_create(ndev, NCI_DESTINATION_NFCC_LOOPBACK,
					 0, 0, NULL);
		if (r != NCI_STATUS_OK)
			return r;

		conn_id = nci_get_conn_info_by_dest_type_params(ndev,
					NCI_DESTINATION_NFCC_LOOPBACK,
					NULL);
	}

	conn_info = nci_get_conn_info_by_conn_id(ndev, conn_id);
	if (!conn_info)
		return -EPROTO;

	/* store cb and context to be used on receiving data */
	conn_info->data_exchange_cb = nci_nfcc_loopback_cb;
	conn_info->data_exchange_cb_context = ndev;

	skb = nci_skb_alloc(ndev, NCI_DATA_HDR_SIZE + data_len, GFP_KERNEL);
	if (!skb)
		return -ENOMEM;

	skb_reserve(skb, NCI_DATA_HDR_SIZE);
	skb_put_data(skb, data, data_len);

	loopback_data.conn_id = conn_id;
	loopback_data.data = skb;

	ndev->cur_conn_id = conn_id;
	r = nci_request(ndev, nci_send_data_req, (unsigned long)&loopback_data,
			msecs_to_jiffies(NCI_DATA_TIMEOUT));
	if (r == NCI_STATUS_OK && resp)
		*resp = conn_info->rx_skb;

	return r;
}