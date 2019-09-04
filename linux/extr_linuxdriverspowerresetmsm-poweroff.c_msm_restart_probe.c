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
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 int /*<<< orphan*/  do_msm_poweroff ; 
 int /*<<< orphan*/  msm_ps_hold ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_power_off ; 
 int /*<<< orphan*/  register_restart_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restart_nb ; 

__attribute__((used)) static int msm_restart_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *mem;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	msm_ps_hold = devm_ioremap_resource(dev, mem);
	if (IS_ERR(msm_ps_hold))
		return PTR_ERR(msm_ps_hold);

	register_restart_handler(&restart_nb);

	pm_power_off = do_msm_poweroff;

	return 0;
}