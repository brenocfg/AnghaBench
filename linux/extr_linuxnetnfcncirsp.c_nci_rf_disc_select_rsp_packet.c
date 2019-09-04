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
struct sk_buff {scalar_t__* data; } ;
struct nci_dev {int dummy; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 scalar_t__ NCI_STATUS_OK ; 
 int /*<<< orphan*/  nci_req_complete (struct nci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 

__attribute__((used)) static void nci_rf_disc_select_rsp_packet(struct nci_dev *ndev,
					  struct sk_buff *skb)
{
	__u8 status = skb->data[0];

	pr_debug("status 0x%x\n", status);

	/* Complete the request on intf_activated_ntf or generic_error_ntf */
	if (status != NCI_STATUS_OK)
		nci_req_complete(ndev, status);
}