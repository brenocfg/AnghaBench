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
typedef  int /*<<< orphan*/  u32 ;
struct nfc_dev {int dummy; } ;
struct nci_dev {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* enable_se ) (struct nci_dev*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct nci_dev* nfc_get_drvdata (struct nfc_dev*) ; 
 int stub1 (struct nci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nci_enable_se(struct nfc_dev *nfc_dev, u32 se_idx)
{
	struct nci_dev *ndev = nfc_get_drvdata(nfc_dev);

	if (ndev->ops->enable_se)
		return ndev->ops->enable_se(ndev, se_idx);

	return 0;
}