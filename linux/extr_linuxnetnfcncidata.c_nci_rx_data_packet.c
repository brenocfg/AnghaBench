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
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;
struct nci_dev {scalar_t__ target_active_prot; } ;
struct nci_conn_info {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_DATA_HDR_SIZE ; 
 scalar_t__ NFC_PROTO_FELICA ; 
 scalar_t__ NFC_PROTO_ISO15693 ; 
 scalar_t__ NFC_PROTO_JEWEL ; 
 scalar_t__ NFC_PROTO_MIFARE ; 
 int /*<<< orphan*/  nci_add_rx_data_frag (struct nci_dev*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_conn_id (int /*<<< orphan*/ *) ; 
 struct nci_conn_info* nci_get_conn_info_by_conn_id (struct nci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_pbf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nci_plen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nci_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

void nci_rx_data_packet(struct nci_dev *ndev, struct sk_buff *skb)
{
	__u8 pbf = nci_pbf(skb->data);
	__u8 status = 0;
	__u8 conn_id = nci_conn_id(skb->data);
	struct nci_conn_info    *conn_info;

	pr_debug("len %d\n", skb->len);

	pr_debug("NCI RX: MT=data, PBF=%d, conn_id=%d, plen=%d\n",
		 nci_pbf(skb->data),
		 nci_conn_id(skb->data),
		 nci_plen(skb->data));

	conn_info = nci_get_conn_info_by_conn_id(ndev, nci_conn_id(skb->data));
	if (!conn_info)
		return;

	/* strip the nci data header */
	skb_pull(skb, NCI_DATA_HDR_SIZE);

	if (ndev->target_active_prot == NFC_PROTO_MIFARE ||
	    ndev->target_active_prot == NFC_PROTO_JEWEL ||
	    ndev->target_active_prot == NFC_PROTO_FELICA ||
	    ndev->target_active_prot == NFC_PROTO_ISO15693) {
		/* frame I/F => remove the status byte */
		pr_debug("frame I/F => remove the status byte\n");
		status = skb->data[skb->len - 1];
		skb_trim(skb, (skb->len - 1));
	}

	nci_add_rx_data_frag(ndev, skb, pbf, conn_id, nci_to_errno(status));
}