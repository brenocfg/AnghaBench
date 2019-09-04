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
 int /*<<< orphan*/  platform_driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_rmtfs_mem_driver ; 
 int /*<<< orphan*/  qcom_rmtfs_mem_major ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qcom_rmtfs_mem_exit(void)
{
	platform_driver_unregister(&qcom_rmtfs_mem_driver);
	unregister_chrdev_region(qcom_rmtfs_mem_major, QCOM_RMTFS_MEM_DEV_MAX);
}