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
struct uctrl_driver {int /*<<< orphan*/  regs; int /*<<< orphan*/  irq; } ;
struct platform_device {int /*<<< orphan*/ * resource; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct uctrl_driver* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uctrl_driver*) ; 
 int /*<<< orphan*/  kfree (struct uctrl_driver*) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uctrl_dev ; 

__attribute__((used)) static int uctrl_remove(struct platform_device *op)
{
	struct uctrl_driver *p = dev_get_drvdata(&op->dev);

	if (p) {
		misc_deregister(&uctrl_dev);
		free_irq(p->irq, p);
		of_iounmap(&op->resource[0], p->regs, resource_size(&op->resource[0]));
		kfree(p);
	}
	return 0;
}