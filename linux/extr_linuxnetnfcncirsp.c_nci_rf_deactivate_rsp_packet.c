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
struct nci_dev {int /*<<< orphan*/  state; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_IDLE ; 
 scalar_t__ NCI_POLL_ACTIVE ; 
 scalar_t__ NCI_STATUS_OK ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_clear_target_list (struct nci_dev*) ; 
 int /*<<< orphan*/  nci_req_complete (struct nci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 

__attribute__((used)) static void nci_rf_deactivate_rsp_packet(struct nci_dev *ndev,
					 struct sk_buff *skb)
{
	__u8 status = skb->data[0];

	pr_debug("status 0x%x\n", status);

	/* If target was active, complete the request only in deactivate_ntf */
	if ((status != NCI_STATUS_OK) ||
	    (atomic_read(&ndev->state) != NCI_POLL_ACTIVE)) {
		nci_clear_target_list(ndev);
		atomic_set(&ndev->state, NCI_IDLE);
		nci_req_complete(ndev, status);
	}
}