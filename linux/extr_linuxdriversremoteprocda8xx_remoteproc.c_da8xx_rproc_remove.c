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
struct rproc {scalar_t__ priv; } ;
struct device {scalar_t__ of_node; } ;
struct platform_device {struct device dev; } ;
struct da8xx_rproc {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_reserved_mem_device_release (struct device*) ; 
 struct rproc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rproc_del (struct rproc*) ; 
 int /*<<< orphan*/  rproc_free (struct rproc*) ; 

__attribute__((used)) static int da8xx_rproc_remove(struct platform_device *pdev)
{
	struct rproc *rproc = platform_get_drvdata(pdev);
	struct da8xx_rproc *drproc = (struct da8xx_rproc *)rproc->priv;
	struct device *dev = &pdev->dev;

	/*
	 * The devm subsystem might end up releasing things before
	 * freeing the irq, thus allowing an interrupt to sneak in while
	 * the device is being removed.  This should prevent that.
	 */
	disable_irq(drproc->irq);

	rproc_del(rproc);
	rproc_free(rproc);
	if (dev->of_node)
		of_reserved_mem_device_release(dev);

	return 0;
}