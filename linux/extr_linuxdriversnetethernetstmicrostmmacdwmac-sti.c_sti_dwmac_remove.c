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
struct sti_dwmac {int /*<<< orphan*/  clk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sti_dwmac* get_stmmac_bsp_priv (int /*<<< orphan*/ *) ; 
 int stmmac_dvr_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sti_dwmac_remove(struct platform_device *pdev)
{
	struct sti_dwmac *dwmac = get_stmmac_bsp_priv(&pdev->dev);
	int ret = stmmac_dvr_remove(&pdev->dev);

	clk_disable_unprepare(dwmac->clk);

	return ret;
}