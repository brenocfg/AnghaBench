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
struct platform_device {int dummy; } ;
struct iproc_pwmc {int /*<<< orphan*/  chip; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct iproc_pwmc* platform_get_drvdata (struct platform_device*) ; 
 int pwmchip_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iproc_pwmc_remove(struct platform_device *pdev)
{
	struct iproc_pwmc *ip = platform_get_drvdata(pdev);

	clk_disable_unprepare(ip->clk);

	return pwmchip_remove(&ip->chip);
}