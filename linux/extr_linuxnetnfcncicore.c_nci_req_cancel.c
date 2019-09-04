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
struct nci_dev {scalar_t__ req_status; int req_result; int /*<<< orphan*/  req_completion; } ;

/* Variables and functions */
 scalar_t__ NCI_REQ_CANCELED ; 
 scalar_t__ NCI_REQ_PEND ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nci_req_cancel(struct nci_dev *ndev, int err)
{
	if (ndev->req_status == NCI_REQ_PEND) {
		ndev->req_result = err;
		ndev->req_status = NCI_REQ_CANCELED;
		complete(&ndev->req_completion);
	}
}