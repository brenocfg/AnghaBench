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
struct nfcmrvl_private {TYPE_1__* if_ops; int /*<<< orphan*/  flags; } ;
struct nci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* nci_close ) (struct nfcmrvl_private*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NFCMRVL_NCI_RUNNING ; 
 struct nfcmrvl_private* nci_get_drvdata (struct nci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct nfcmrvl_private*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfcmrvl_nci_close(struct nci_dev *ndev)
{
	struct nfcmrvl_private *priv = nci_get_drvdata(ndev);

	if (!test_and_clear_bit(NFCMRVL_NCI_RUNNING, &priv->flags))
		return 0;

	priv->if_ops->nci_close(priv);

	return 0;
}