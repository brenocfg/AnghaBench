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
struct platform_device {int dummy; } ;
struct parport {int /*<<< orphan*/  irq; } ;
struct ax_drvdata {TYPE_1__* io; int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct parport*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ax_drvdata*) ; 
 int /*<<< orphan*/  parport_remove_port (struct parport*) ; 
 struct parport* platform_get_drvdata (struct platform_device*) ; 
 struct ax_drvdata* pp_to_drv (struct parport*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 

__attribute__((used)) static int parport_ax88796_remove(struct platform_device *pdev)
{
	struct parport *p = platform_get_drvdata(pdev);
	struct ax_drvdata *dd = pp_to_drv(p);

	free_irq(p->irq, p);
	parport_remove_port(p);
	iounmap(dd->base);
	release_mem_region(dd->io->start, resource_size(dd->io));
	kfree(dd);

	return 0;
}