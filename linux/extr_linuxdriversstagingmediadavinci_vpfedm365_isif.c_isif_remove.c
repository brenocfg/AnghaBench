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
struct TYPE_2__ {int /*<<< orphan*/  linear_tbl1_addr; int /*<<< orphan*/  linear_tbl0_addr; int /*<<< orphan*/  base_addr; } ;
struct vpfe_isif_device {TYPE_1__ isif_cfg; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static void isif_remove(struct vpfe_isif_device *isif,
			struct platform_device *pdev)
{
	struct resource *res;
	int i = 0;

	iounmap(isif->isif_cfg.base_addr);
	iounmap(isif->isif_cfg.linear_tbl0_addr);
	iounmap(isif->isif_cfg.linear_tbl1_addr);

	while (i < 3) {
		res = platform_get_resource(pdev, IORESOURCE_MEM, i);
		if (res)
			release_mem_region(res->start,
					   resource_size(res));
		i++;
	}
}