#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__* data; } ;
struct TYPE_6__ {scalar_t__ id; int /*<<< orphan*/  protocol; } ;
struct nci_dev {TYPE_4__* nfc_dev; TYPE_3__* hci_dev; TYPE_2__ cur_params; int /*<<< orphan*/  conn_info_list; int /*<<< orphan*/  cur_dest_type; } ;
struct nci_core_conn_create_rsp {int /*<<< orphan*/  credits_cnt; int /*<<< orphan*/  max_ctrl_pkt_payload_len; int /*<<< orphan*/  conn_id; } ;
struct nci_conn_info {int /*<<< orphan*/  credits_cnt; int /*<<< orphan*/  max_pkt_payload_len; int /*<<< orphan*/  conn_id; int /*<<< orphan*/  list; TYPE_1__* dest_params; int /*<<< orphan*/  dest_type; } ;
struct dest_spec_params {int dummy; } ;
typedef  scalar_t__ __u8 ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {scalar_t__ nfcee_id; struct nci_conn_info* conn_info; } ;
struct TYPE_5__ {scalar_t__ id; int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ NCI_STATUS_OK ; 
 scalar_t__ NCI_STATUS_REJECTED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct nci_conn_info*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nci_req_complete (struct nci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 

__attribute__((used)) static void nci_core_conn_create_rsp_packet(struct nci_dev *ndev,
					    struct sk_buff *skb)
{
	__u8 status = skb->data[0];
	struct nci_conn_info *conn_info = NULL;
	struct nci_core_conn_create_rsp *rsp;

	pr_debug("status 0x%x\n", status);

	if (status == NCI_STATUS_OK) {
		rsp = (struct nci_core_conn_create_rsp *)skb->data;

		conn_info = devm_kzalloc(&ndev->nfc_dev->dev,
					 sizeof(*conn_info), GFP_KERNEL);
		if (!conn_info) {
			status = NCI_STATUS_REJECTED;
			goto exit;
		}

		conn_info->dest_params = devm_kzalloc(&ndev->nfc_dev->dev,
						sizeof(struct dest_spec_params),
						GFP_KERNEL);
		if (!conn_info->dest_params) {
			status = NCI_STATUS_REJECTED;
			goto free_conn_info;
		}

		conn_info->dest_type = ndev->cur_dest_type;
		conn_info->dest_params->id = ndev->cur_params.id;
		conn_info->dest_params->protocol = ndev->cur_params.protocol;
		conn_info->conn_id = rsp->conn_id;

		/* Note: data_exchange_cb and data_exchange_cb_context need to
		 * be specify out of nci_core_conn_create_rsp_packet
		 */

		INIT_LIST_HEAD(&conn_info->list);
		list_add(&conn_info->list, &ndev->conn_info_list);

		if (ndev->cur_params.id == ndev->hci_dev->nfcee_id)
			ndev->hci_dev->conn_info = conn_info;

		conn_info->conn_id = rsp->conn_id;
		conn_info->max_pkt_payload_len = rsp->max_ctrl_pkt_payload_len;
		atomic_set(&conn_info->credits_cnt, rsp->credits_cnt);
	}

free_conn_info:
	if (status == NCI_STATUS_REJECTED)
		devm_kfree(&ndev->nfc_dev->dev, conn_info);
exit:

	nci_req_complete(ndev, status);
}