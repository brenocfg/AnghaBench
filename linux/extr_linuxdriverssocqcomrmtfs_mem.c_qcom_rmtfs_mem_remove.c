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
struct qcom_scm_vmperm {int /*<<< orphan*/  perm; int /*<<< orphan*/  vmid; } ;
struct qcom_rmtfs_mem {int /*<<< orphan*/  dev; int /*<<< orphan*/  cdev; scalar_t__ perms; int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCOM_SCM_PERM_RW ; 
 int /*<<< orphan*/  QCOM_SCM_VMID_HLOS ; 
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct qcom_rmtfs_mem* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_scm_assign_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,struct qcom_scm_vmperm*,int) ; 

__attribute__((used)) static int qcom_rmtfs_mem_remove(struct platform_device *pdev)
{
	struct qcom_rmtfs_mem *rmtfs_mem = dev_get_drvdata(&pdev->dev);
	struct qcom_scm_vmperm perm;

	if (rmtfs_mem->perms) {
		perm.vmid = QCOM_SCM_VMID_HLOS;
		perm.perm = QCOM_SCM_PERM_RW;

		qcom_scm_assign_mem(rmtfs_mem->addr, rmtfs_mem->size,
				    &rmtfs_mem->perms, &perm, 1);
	}

	cdev_device_del(&rmtfs_mem->cdev, &rmtfs_mem->dev);
	put_device(&rmtfs_mem->dev);

	return 0;
}