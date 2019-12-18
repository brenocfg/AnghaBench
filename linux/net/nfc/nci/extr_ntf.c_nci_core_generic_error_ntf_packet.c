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
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct nci_dev {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 scalar_t__ NCI_W4_HOST_SELECT ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nci_req_complete (struct nci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nci_core_generic_error_ntf_packet(struct nci_dev *ndev,
					      struct sk_buff *skb)
{
	__u8 status = skb->data[0];

	pr_debug("status 0x%x\n", status);

	if (atomic_read(&ndev->state) == NCI_W4_HOST_SELECT) {
		/* Activation failed, so complete the request
		   (the state remains the same) */
		nci_req_complete(ndev, status);
	}
}