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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_smd_remove_edge ; 

__attribute__((used)) static int qcom_smd_remove(struct platform_device *pdev)
{
	int ret;

	ret = device_for_each_child(&pdev->dev, NULL, qcom_smd_remove_edge);
	if (ret)
		dev_warn(&pdev->dev, "can't remove smd device: %d\n", ret);

	return ret;
}