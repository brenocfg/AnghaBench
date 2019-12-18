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
struct sk_buff {scalar_t__* data; } ;
struct nci_dev {TYPE_1__* nfc_dev; int /*<<< orphan*/  cur_conn_id; } ;
struct nci_conn_info {int /*<<< orphan*/  list; } ;
typedef  scalar_t__ __u8 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ NCI_STATUS_OK ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct nci_conn_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct nci_conn_info* nci_get_conn_info_by_conn_id (struct nci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_req_complete (struct nci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 

__attribute__((used)) static void nci_core_conn_close_rsp_packet(struct nci_dev *ndev,
					   struct sk_buff *skb)
{
	struct nci_conn_info *conn_info;
	__u8 status = skb->data[0];

	pr_debug("status 0x%x\n", status);
	if (status == NCI_STATUS_OK) {
		conn_info = nci_get_conn_info_by_conn_id(ndev,
							 ndev->cur_conn_id);
		if (conn_info) {
			list_del(&conn_info->list);
			devm_kfree(&ndev->nfc_dev->dev, conn_info);
		}
	}
	nci_req_complete(ndev, status);
}