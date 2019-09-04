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
struct nfcmrvl_private {int /*<<< orphan*/  flags; TYPE_1__* if_ops; } ;
struct nci_dev {int dummy; } ;
struct TYPE_2__ {int (* nci_open ) (struct nfcmrvl_private*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NFCMRVL_NCI_RUNNING ; 
 int /*<<< orphan*/  NFCMRVL_PHY_ERROR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nfcmrvl_private* nci_get_drvdata (struct nci_dev*) ; 
 int stub1 (struct nfcmrvl_private*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfcmrvl_nci_open(struct nci_dev *ndev)
{
	struct nfcmrvl_private *priv = nci_get_drvdata(ndev);
	int err;

	if (test_and_set_bit(NFCMRVL_NCI_RUNNING, &priv->flags))
		return 0;

	/* Reset possible fault of previous session */
	clear_bit(NFCMRVL_PHY_ERROR, &priv->flags);

	err = priv->if_ops->nci_open(priv);

	if (err)
		clear_bit(NFCMRVL_NCI_RUNNING, &priv->flags);

	return err;
}