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
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_client ; 
 int /*<<< orphan*/  platform_driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qmi_debug_dir ; 
 int /*<<< orphan*/  qmi_handle_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qmi_sample_driver ; 

__attribute__((used)) static void qmi_sample_exit(void)
{
	qmi_handle_release(&lookup_client);

	platform_driver_unregister(&qmi_sample_driver);

	debugfs_remove(qmi_debug_dir);
}