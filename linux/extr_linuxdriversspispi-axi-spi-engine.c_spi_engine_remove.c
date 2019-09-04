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
struct spi_master {int dummy; } ;
struct spi_engine {int /*<<< orphan*/  clk; int /*<<< orphan*/  ref_clk; scalar_t__ base; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SPI_ENGINE_REG_INT_ENABLE ; 
 scalar_t__ SPI_ENGINE_REG_INT_PENDING ; 
 scalar_t__ SPI_ENGINE_REG_RESET ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int,struct spi_master*) ; 
 int /*<<< orphan*/  platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct spi_master* spi_master_get (int /*<<< orphan*/ ) ; 
 struct spi_engine* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int /*<<< orphan*/  spi_unregister_master (struct spi_master*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int spi_engine_remove(struct platform_device *pdev)
{
	struct spi_master *master = spi_master_get(platform_get_drvdata(pdev));
	struct spi_engine *spi_engine = spi_master_get_devdata(master);
	int irq = platform_get_irq(pdev, 0);

	spi_unregister_master(master);

	free_irq(irq, master);

	spi_master_put(master);

	writel_relaxed(0xff, spi_engine->base + SPI_ENGINE_REG_INT_PENDING);
	writel_relaxed(0x00, spi_engine->base + SPI_ENGINE_REG_INT_ENABLE);
	writel_relaxed(0x01, spi_engine->base + SPI_ENGINE_REG_RESET);

	clk_disable_unprepare(spi_engine->ref_clk);
	clk_disable_unprepare(spi_engine->clk);

	return 0;
}