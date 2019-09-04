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

/* Variables and functions */
 int /*<<< orphan*/  QCOM_RMTFS_MEM_DEV_MAX ; 
 int alloc_chrdev_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int platform_driver_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  qcom_rmtfs_mem_driver ; 
 int /*<<< orphan*/  qcom_rmtfs_mem_major ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_rmtfs_mem_init(void)
{
	int ret;

	ret = alloc_chrdev_region(&qcom_rmtfs_mem_major, 0,
				  QCOM_RMTFS_MEM_DEV_MAX, "qcom_rmtfs_mem");
	if (ret < 0) {
		pr_err("qcom_rmtfs_mem: failed to allocate char dev region\n");
		return ret;
	}

	ret = platform_driver_register(&qcom_rmtfs_mem_driver);
	if (ret < 0) {
		pr_err("qcom_rmtfs_mem: failed to register rmtfs_mem driver\n");
		unregister_chrdev_region(qcom_rmtfs_mem_major,
					 QCOM_RMTFS_MEM_DEV_MAX);
	}

	return ret;
}