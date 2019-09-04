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
struct vpfe_device {int /*<<< orphan*/  media_dev; int /*<<< orphan*/  v4l2_dev; struct vpfe_device* sd; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kzfree (struct vpfe_device*) ; 
 int /*<<< orphan*/  media_device_unregister (int /*<<< orphan*/ *) ; 
 struct vpfe_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vpfe_cleanup_modules (struct vpfe_device*,struct platform_device*) ; 
 int /*<<< orphan*/  vpfe_detach_irq (struct vpfe_device*) ; 
 int /*<<< orphan*/  vpfe_disable_clock (struct vpfe_device*) ; 
 int /*<<< orphan*/  vpfe_unregister_entities (struct vpfe_device*) ; 

__attribute__((used)) static int vpfe_remove(struct platform_device *pdev)
{
	struct vpfe_device *vpfe_dev = platform_get_drvdata(pdev);

	v4l2_info(pdev->dev.driver, "vpfe_remove\n");

	kzfree(vpfe_dev->sd);
	vpfe_detach_irq(vpfe_dev);
	vpfe_unregister_entities(vpfe_dev);
	vpfe_cleanup_modules(vpfe_dev, pdev);
	v4l2_device_unregister(&vpfe_dev->v4l2_dev);
	media_device_unregister(&vpfe_dev->media_dev);
	vpfe_disable_clock(vpfe_dev);
	kzfree(vpfe_dev);

	return 0;
}