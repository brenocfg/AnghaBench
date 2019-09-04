#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ data; } ;
struct nci_nfcee_discover_ntf {int /*<<< orphan*/  nfcee_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct nci_dev {TYPE_2__ cur_params; TYPE_1__* hci_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  nfcee_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_STATUS_OK ; 
 int /*<<< orphan*/  nci_req_complete (struct nci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void nci_nfcee_discover_ntf_packet(struct nci_dev *ndev,
					  struct sk_buff *skb)
{
	u8 status = NCI_STATUS_OK;
	struct nci_nfcee_discover_ntf   *nfcee_ntf =
				(struct nci_nfcee_discover_ntf *)skb->data;

	pr_debug("\n");

	/* NFCForum NCI 9.2.1 HCI Network Specific Handling
	 * If the NFCC supports the HCI Network, it SHALL return one,
	 * and only one, NFCEE_DISCOVER_NTF with a Protocol type of
	 * “HCI Access”, even if the HCI Network contains multiple NFCEEs.
	 */
	ndev->hci_dev->nfcee_id = nfcee_ntf->nfcee_id;
	ndev->cur_params.id = nfcee_ntf->nfcee_id;

	nci_req_complete(ndev, status);
}