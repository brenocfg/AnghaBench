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
struct rb4xx_spi {int /*<<< orphan*/  clk; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct rb4xx_spi* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int rb4xx_spi_remove(struct platform_device *pdev)
{
	struct rb4xx_spi *rbspi = platform_get_drvdata(pdev);

	clk_disable_unprepare(rbspi->clk);

	return 0;
}