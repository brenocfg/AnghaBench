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
struct s3c24xx_spi {int /*<<< orphan*/  master; int /*<<< orphan*/  clk; int /*<<< orphan*/  bitbang; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct s3c24xx_spi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spi_bitbang_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_master_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3c24xx_spi_remove(struct platform_device *dev)
{
	struct s3c24xx_spi *hw = platform_get_drvdata(dev);

	spi_bitbang_stop(&hw->bitbang);
	clk_disable(hw->clk);
	spi_master_put(hw->master);
	return 0;
}