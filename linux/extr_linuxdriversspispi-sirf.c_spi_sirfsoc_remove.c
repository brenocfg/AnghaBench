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
struct sirfsoc_spi {int /*<<< orphan*/  tx_chan; int /*<<< orphan*/  rx_chan; int /*<<< orphan*/  clk; int /*<<< orphan*/  bitbang; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 struct spi_master* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spi_bitbang_stop (int /*<<< orphan*/ *) ; 
 struct sirfsoc_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 

__attribute__((used)) static int  spi_sirfsoc_remove(struct platform_device *pdev)
{
	struct spi_master *master;
	struct sirfsoc_spi *sspi;

	master = platform_get_drvdata(pdev);
	sspi = spi_master_get_devdata(master);
	spi_bitbang_stop(&sspi->bitbang);
	clk_disable_unprepare(sspi->clk);
	clk_put(sspi->clk);
	dma_release_channel(sspi->rx_chan);
	dma_release_channel(sspi->tx_chan);
	spi_master_put(master);
	return 0;
}