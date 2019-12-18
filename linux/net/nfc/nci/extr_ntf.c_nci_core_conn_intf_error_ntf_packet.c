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
struct nci_dev {int /*<<< orphan*/  flags; } ;
struct nci_core_intf_error_ntf {int /*<<< orphan*/  conn_id; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  NCI_DATA_EXCHANGE ; 
 int /*<<< orphan*/  nci_conn_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nci_data_exchange_complete (struct nci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nci_core_conn_intf_error_ntf_packet(struct nci_dev *ndev,
						struct sk_buff *skb)
{
	struct nci_core_intf_error_ntf *ntf = (void *) skb->data;

	ntf->conn_id = nci_conn_id(&ntf->conn_id);

	pr_debug("status 0x%x, conn_id %d\n", ntf->status, ntf->conn_id);

	/* complete the data exchange transaction, if exists */
	if (test_bit(NCI_DATA_EXCHANGE, &ndev->flags))
		nci_data_exchange_complete(ndev, NULL, ntf->conn_id, -EIO);
}