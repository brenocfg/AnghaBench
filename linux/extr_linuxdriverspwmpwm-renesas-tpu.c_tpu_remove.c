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
struct tpu_device {int /*<<< orphan*/  chip; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct tpu_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int pwmchip_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tpu_remove(struct platform_device *pdev)
{
	struct tpu_device *tpu = platform_get_drvdata(pdev);
	int ret;

	ret = pwmchip_remove(&tpu->chip);
	if (ret)
		return ret;

	pm_runtime_disable(&pdev->dev);

	return 0;
}