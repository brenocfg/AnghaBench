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
struct samsung_spdif_info {int /*<<< orphan*/  pclk; int /*<<< orphan*/  sclk; int /*<<< orphan*/  regs; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 struct samsung_spdif_info spdif_info ; 

__attribute__((used)) static int spdif_remove(struct platform_device *pdev)
{
	struct samsung_spdif_info *spdif = &spdif_info;
	struct resource *mem_res;

	iounmap(spdif->regs);

	mem_res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (mem_res)
		release_mem_region(mem_res->start, resource_size(mem_res));

	clk_disable_unprepare(spdif->sclk);
	clk_disable_unprepare(spdif->pclk);

	return 0;
}