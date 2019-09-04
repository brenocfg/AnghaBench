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
struct nci_dev {int req_status; int req_result; int /*<<< orphan*/  req_completion; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 long ETIMEDOUT ; 
#define  NCI_REQ_CANCELED 129 
#define  NCI_REQ_DONE 128 
 int NCI_REQ_PEND ; 
 int nci_to_errno (int) ; 
 int /*<<< orphan*/  pr_debug (char*,long) ; 
 int /*<<< orphan*/  pr_err (char*,long) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 long wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __nci_request(struct nci_dev *ndev,
			 void (*req)(struct nci_dev *ndev, unsigned long opt),
			 unsigned long opt, __u32 timeout)
{
	int rc = 0;
	long completion_rc;

	ndev->req_status = NCI_REQ_PEND;

	reinit_completion(&ndev->req_completion);
	req(ndev, opt);
	completion_rc =
		wait_for_completion_interruptible_timeout(&ndev->req_completion,
							  timeout);

	pr_debug("wait_for_completion return %ld\n", completion_rc);

	if (completion_rc > 0) {
		switch (ndev->req_status) {
		case NCI_REQ_DONE:
			rc = nci_to_errno(ndev->req_result);
			break;

		case NCI_REQ_CANCELED:
			rc = -ndev->req_result;
			break;

		default:
			rc = -ETIMEDOUT;
			break;
		}
	} else {
		pr_err("wait_for_completion_interruptible_timeout failed %ld\n",
		       completion_rc);

		rc = ((completion_rc == 0) ? (-ETIMEDOUT) : (completion_rc));
	}

	ndev->req_status = ndev->req_result = 0;

	return rc;
}