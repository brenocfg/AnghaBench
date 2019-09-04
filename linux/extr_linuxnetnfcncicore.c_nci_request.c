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
struct nci_dev {int /*<<< orphan*/  req_lock; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int ENETDOWN ; 
 int /*<<< orphan*/  NCI_UP ; 
 int __nci_request (struct nci_dev*,void (*) (struct nci_dev*,unsigned long),unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

inline int nci_request(struct nci_dev *ndev,
		       void (*req)(struct nci_dev *ndev,
				   unsigned long opt),
		       unsigned long opt, __u32 timeout)
{
	int rc;

	if (!test_bit(NCI_UP, &ndev->flags))
		return -ENETDOWN;

	/* Serialize all requests */
	mutex_lock(&ndev->req_lock);
	rc = __nci_request(ndev, req, opt, timeout);
	mutex_unlock(&ndev->req_lock);

	return rc;
}