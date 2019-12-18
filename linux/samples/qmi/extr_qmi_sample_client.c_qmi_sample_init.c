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
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_client ; 
 int /*<<< orphan*/  lookup_ops ; 
 int platform_driver_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  qmi_add_lookup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qmi_debug_dir ; 
 int qmi_handle_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qmi_sample_driver ; 

__attribute__((used)) static int qmi_sample_init(void)
{
	int ret;

	qmi_debug_dir = debugfs_create_dir("qmi_sample", NULL);
	if (IS_ERR(qmi_debug_dir)) {
		pr_err("failed to create qmi_sample dir\n");
		return PTR_ERR(qmi_debug_dir);
	}

	ret = platform_driver_register(&qmi_sample_driver);
	if (ret)
		goto err_remove_debug_dir;

	ret = qmi_handle_init(&lookup_client, 0, &lookup_ops, NULL);
	if (ret < 0)
		goto err_unregister_driver;

	qmi_add_lookup(&lookup_client, 15, 0, 0);

	return 0;

err_unregister_driver:
	platform_driver_unregister(&qmi_sample_driver);
err_remove_debug_dir:
	debugfs_remove(qmi_debug_dir);

	return ret;
}