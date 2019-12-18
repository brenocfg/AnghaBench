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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct nci_dev {TYPE_1__* hci_dev; } ;
struct nci_conn_info {struct sk_buff* rx_skb; } ;
struct TYPE_2__ {struct nci_conn_info* conn_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_STATUS_OK ; 
 int /*<<< orphan*/  NCI_STATUS_REJECTED ; 
 int /*<<< orphan*/  nci_req_complete (struct nci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nci_hci_resp_received(struct nci_dev *ndev, u8 pipe,
				  u8 result, struct sk_buff *skb)
{
	struct nci_conn_info    *conn_info;
	u8 status = result;

	conn_info = ndev->hci_dev->conn_info;
	if (!conn_info) {
		status = NCI_STATUS_REJECTED;
		goto exit;
	}

	conn_info->rx_skb = skb;

exit:
	nci_req_complete(ndev, NCI_STATUS_OK);
}