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
struct vlynq_device {scalar_t__ regs_start; scalar_t__ regs_end; int /*<<< orphan*/  local; int /*<<< orphan*/  dev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vlynq_device*) ; 
 struct vlynq_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int vlynq_remove(struct platform_device *pdev)
{
	struct vlynq_device *dev = platform_get_drvdata(pdev);

	device_unregister(&dev->dev);
	iounmap(dev->local);
	release_mem_region(dev->regs_start,
			   dev->regs_end - dev->regs_start + 1);

	kfree(dev);

	return 0;
}