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
struct qmi_sample {int /*<<< orphan*/  qmi; int /*<<< orphan*/  de_dir; int /*<<< orphan*/  de_data; int /*<<< orphan*/  de_ping; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 struct qmi_sample* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  qmi_handle_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qmi_sample_remove(struct platform_device *pdev)
{
	struct qmi_sample *sample = platform_get_drvdata(pdev);

	debugfs_remove(sample->de_ping);
	debugfs_remove(sample->de_data);
	debugfs_remove(sample->de_dir);

	qmi_handle_release(&sample->qmi);

	return 0;
}