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
struct nfc_target {int /*<<< orphan*/  idx; } ;
struct nfc_dev {int dummy; } ;
struct nci_dev {int /*<<< orphan*/  flags; int /*<<< orphan*/  target_active_prot; struct nci_conn_info* rf_conn_info; } ;
struct nci_conn_info {void* data_exchange_cb_context; int /*<<< orphan*/  data_exchange_cb; } ;
typedef  int /*<<< orphan*/  data_exchange_cb_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EPROTO ; 
 int /*<<< orphan*/  NCI_DATA_EXCHANGE ; 
 int /*<<< orphan*/  NCI_STATIC_RF_CONN_ID ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nci_send_data (struct nci_dev*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct nci_dev* nfc_get_drvdata (struct nfc_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nci_transceive(struct nfc_dev *nfc_dev, struct nfc_target *target,
			  struct sk_buff *skb,
			  data_exchange_cb_t cb, void *cb_context)
{
	struct nci_dev *ndev = nfc_get_drvdata(nfc_dev);
	int rc;
	struct nci_conn_info    *conn_info;

	conn_info = ndev->rf_conn_info;
	if (!conn_info)
		return -EPROTO;

	pr_debug("target_idx %d, len %d\n", target->idx, skb->len);

	if (!ndev->target_active_prot) {
		pr_err("unable to exchange data, no active target\n");
		return -EINVAL;
	}

	if (test_and_set_bit(NCI_DATA_EXCHANGE, &ndev->flags))
		return -EBUSY;

	/* store cb and context to be used on receiving data */
	conn_info->data_exchange_cb = cb;
	conn_info->data_exchange_cb_context = cb_context;

	rc = nci_send_data(ndev, NCI_STATIC_RF_CONN_ID, skb);
	if (rc)
		clear_bit(NCI_DATA_EXCHANGE, &ndev->flags);

	return rc;
}