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
struct nfc_dev {int dummy; } ;
struct nci_dev {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* discover_se ) (struct nci_dev*) ;} ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  NCI_NFCEE_DISCOVERY_ACTION_ENABLE ; 
 int NCI_STATUS_OK ; 
 int nci_nfcee_discover (struct nci_dev*,int /*<<< orphan*/ ) ; 
 struct nci_dev* nfc_get_drvdata (struct nfc_dev*) ; 
 int stub1 (struct nci_dev*) ; 

__attribute__((used)) static int nci_discover_se(struct nfc_dev *nfc_dev)
{
	int r;
	struct nci_dev *ndev = nfc_get_drvdata(nfc_dev);

	if (ndev->ops->discover_se) {
		r = nci_nfcee_discover(ndev, NCI_NFCEE_DISCOVERY_ACTION_ENABLE);
		if (r != NCI_STATUS_OK)
			return -EPROTO;

		return ndev->ops->discover_se(ndev);
	}

	return 0;
}