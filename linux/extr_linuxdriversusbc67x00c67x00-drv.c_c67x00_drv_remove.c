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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct c67x00_device {TYPE_1__ hpi; int /*<<< orphan*/ * sie; } ;

/* Variables and functions */
 int C67X00_SIES ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  c67x00_ll_release (struct c67x00_device*) ; 
 int /*<<< orphan*/  c67x00_remove_sie (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct c67x00_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct c67x00_device*) ; 
 struct c67x00_device* platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int c67x00_drv_remove(struct platform_device *pdev)
{
	struct c67x00_device *c67x00 = platform_get_drvdata(pdev);
	struct resource *res;
	int i;

	for (i = 0; i < C67X00_SIES; i++)
		c67x00_remove_sie(&c67x00->sie[i]);

	c67x00_ll_release(c67x00);

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (res)
		free_irq(res->start, c67x00);

	iounmap(c67x00->hpi.base);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res)
		release_mem_region(res->start, resource_size(res));

	kfree(c67x00);

	return 0;
}