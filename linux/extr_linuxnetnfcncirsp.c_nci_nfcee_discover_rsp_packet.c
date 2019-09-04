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
struct sk_buff {int len; scalar_t__ data; } ;
struct nci_nfcee_discover_rsp {scalar_t__ status; scalar_t__ num_nfcee; } ;
struct nci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ NCI_STATUS_NFCEE_PROTOCOL_ERROR ; 
 scalar_t__ NCI_STATUS_OK ; 
 int /*<<< orphan*/  nci_req_complete (struct nci_dev*,scalar_t__) ; 

__attribute__((used)) static void nci_nfcee_discover_rsp_packet(struct nci_dev *ndev,
					  struct sk_buff *skb)
{
	struct nci_nfcee_discover_rsp *discover_rsp;

	if (skb->len != 2) {
		nci_req_complete(ndev, NCI_STATUS_NFCEE_PROTOCOL_ERROR);
		return;
	}

	discover_rsp = (struct nci_nfcee_discover_rsp *)skb->data;

	if (discover_rsp->status != NCI_STATUS_OK ||
	    discover_rsp->num_nfcee == 0)
		nci_req_complete(ndev, discover_rsp->status);
}