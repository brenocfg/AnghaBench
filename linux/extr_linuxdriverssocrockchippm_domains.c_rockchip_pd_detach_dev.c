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
struct generic_pm_domain {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_clk_destroy (struct device*) ; 

__attribute__((used)) static void rockchip_pd_detach_dev(struct generic_pm_domain *genpd,
				   struct device *dev)
{
	dev_dbg(dev, "detaching from power domain '%s'\n", genpd->name);

	pm_clk_destroy(dev);
}