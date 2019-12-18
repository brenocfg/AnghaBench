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
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct nci_dev {TYPE_1__* nfc_dev; struct sk_buff* rx_data_reassembly; } ;
typedef  int __u8 ;
struct TYPE_2__ {scalar_t__ rf_mode; } ;

/* Variables and functions */
 int ENOMEM ; 
 int NCI_PBF_CONT ; 
 scalar_t__ NFC_RF_TARGET ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nci_data_exchange_complete (struct nci_dev*,struct sk_buff*,int,int) ; 
 int nfc_tm_data_received (TYPE_1__*,struct sk_buff*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static void nci_add_rx_data_frag(struct nci_dev *ndev,
				 struct sk_buff *skb,
				 __u8 pbf, __u8 conn_id, __u8 status)
{
	int reassembly_len;
	int err = 0;

	if (status) {
		err = status;
		goto exit;
	}

	if (ndev->rx_data_reassembly) {
		reassembly_len = ndev->rx_data_reassembly->len;

		/* first, make enough room for the already accumulated data */
		if (skb_cow_head(skb, reassembly_len)) {
			pr_err("error adding room for accumulated rx data\n");

			kfree_skb(skb);
			skb = NULL;

			kfree_skb(ndev->rx_data_reassembly);
			ndev->rx_data_reassembly = NULL;

			err = -ENOMEM;
			goto exit;
		}

		/* second, combine the two fragments */
		memcpy(skb_push(skb, reassembly_len),
		       ndev->rx_data_reassembly->data,
		       reassembly_len);

		/* third, free old reassembly */
		kfree_skb(ndev->rx_data_reassembly);
		ndev->rx_data_reassembly = NULL;
	}

	if (pbf == NCI_PBF_CONT) {
		/* need to wait for next fragment, store skb and exit */
		ndev->rx_data_reassembly = skb;
		return;
	}

exit:
	if (ndev->nfc_dev->rf_mode == NFC_RF_TARGET) {
		/* Data received in Target mode, forward to nfc core */
		err = nfc_tm_data_received(ndev->nfc_dev, skb);
		if (err)
			pr_err("unable to handle received data\n");
	} else {
		nci_data_exchange_complete(ndev, skb, conn_id, err);
	}
}