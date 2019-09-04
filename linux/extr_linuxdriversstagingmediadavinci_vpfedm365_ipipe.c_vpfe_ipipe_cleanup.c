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
struct vpfe_ipipe_device {int /*<<< orphan*/  isp5_base_addr; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  ctrls; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

void vpfe_ipipe_cleanup(struct vpfe_ipipe_device *ipipe,
			struct platform_device *pdev)
{
	struct resource *res;

	v4l2_ctrl_handler_free(&ipipe->ctrls);

	iounmap(ipipe->base_addr);
	iounmap(ipipe->isp5_base_addr);
	res = platform_get_resource(pdev, IORESOURCE_MEM, 4);
	if (res)
		release_mem_region(res->start, resource_size(res));
}