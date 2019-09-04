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
struct sk_buff {scalar_t__ data; } ;
struct nci_rf_deactivate_ntf {int type; int /*<<< orphan*/  reason; } ;
struct nci_dev {int /*<<< orphan*/  state; int /*<<< orphan*/  flags; int /*<<< orphan*/ * rx_data_reassembly; int /*<<< orphan*/  tx_q; struct nci_conn_info* rf_conn_info; } ;
struct nci_conn_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  NCI_DATA_EXCHANGE ; 
#define  NCI_DEACTIVATE_TYPE_DISCOVERY 131 
#define  NCI_DEACTIVATE_TYPE_IDLE_MODE 130 
#define  NCI_DEACTIVATE_TYPE_SLEEP_AF_MODE 129 
#define  NCI_DEACTIVATE_TYPE_SLEEP_MODE 128 
 int /*<<< orphan*/  NCI_DISCOVERY ; 
 int /*<<< orphan*/  NCI_IDLE ; 
 int /*<<< orphan*/  NCI_STATIC_RF_CONN_ID ; 
 int /*<<< orphan*/  NCI_STATUS_OK ; 
 int /*<<< orphan*/  NCI_W4_HOST_SELECT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nci_clear_target_list (struct nci_dev*) ; 
 int /*<<< orphan*/  nci_data_exchange_complete (struct nci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_req_complete (struct nci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nci_rf_deactivate_ntf_packet(struct nci_dev *ndev,
					 struct sk_buff *skb)
{
	struct nci_conn_info    *conn_info;
	struct nci_rf_deactivate_ntf *ntf = (void *) skb->data;

	pr_debug("entry, type 0x%x, reason 0x%x\n", ntf->type, ntf->reason);

	conn_info = ndev->rf_conn_info;
	if (!conn_info)
		return;

	/* drop tx data queue */
	skb_queue_purge(&ndev->tx_q);

	/* drop partial rx data packet */
	if (ndev->rx_data_reassembly) {
		kfree_skb(ndev->rx_data_reassembly);
		ndev->rx_data_reassembly = NULL;
	}

	/* complete the data exchange transaction, if exists */
	if (test_bit(NCI_DATA_EXCHANGE, &ndev->flags))
		nci_data_exchange_complete(ndev, NULL, NCI_STATIC_RF_CONN_ID,
					   -EIO);

	switch (ntf->type) {
	case NCI_DEACTIVATE_TYPE_IDLE_MODE:
		nci_clear_target_list(ndev);
		atomic_set(&ndev->state, NCI_IDLE);
		break;
	case NCI_DEACTIVATE_TYPE_SLEEP_MODE:
	case NCI_DEACTIVATE_TYPE_SLEEP_AF_MODE:
		atomic_set(&ndev->state, NCI_W4_HOST_SELECT);
		break;
	case NCI_DEACTIVATE_TYPE_DISCOVERY:
		nci_clear_target_list(ndev);
		atomic_set(&ndev->state, NCI_DISCOVERY);
		break;
	}

	nci_req_complete(ndev, NCI_STATUS_OK);
}