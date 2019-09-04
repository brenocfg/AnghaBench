#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  work; } ;
struct nxp_nci_info {scalar_t__ mode; int /*<<< orphan*/  info_lock; int /*<<< orphan*/  phy_id; TYPE_2__* phy_ops; TYPE_1__ fw_info; } ;
struct nci_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_mode ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ESHUTDOWN ; 
 int /*<<< orphan*/  NXP_NCI_MODE_COLD ; 
 scalar_t__ NXP_NCI_MODE_FW ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nci_free_device (struct nci_dev*) ; 
 struct nxp_nci_info* nci_get_drvdata (struct nci_dev*) ; 
 int /*<<< orphan*/  nci_unregister_device (struct nci_dev*) ; 
 int /*<<< orphan*/  nxp_nci_fw_work_complete (struct nxp_nci_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void nxp_nci_remove(struct nci_dev *ndev)
{
	struct nxp_nci_info *info = nci_get_drvdata(ndev);

	if (info->mode == NXP_NCI_MODE_FW)
		nxp_nci_fw_work_complete(info, -ESHUTDOWN);
	cancel_work_sync(&info->fw_info.work);

	mutex_lock(&info->info_lock);

	if (info->phy_ops->set_mode)
		info->phy_ops->set_mode(info->phy_id, NXP_NCI_MODE_COLD);

	nci_unregister_device(ndev);
	nci_free_device(ndev);

	mutex_unlock(&info->info_lock);
}