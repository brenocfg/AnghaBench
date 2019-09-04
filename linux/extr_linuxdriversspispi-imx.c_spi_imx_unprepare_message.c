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
struct spi_message {int dummy; } ;
struct spi_master {int dummy; } ;
struct spi_imx_data {int /*<<< orphan*/  clk_per; int /*<<< orphan*/  clk_ipg; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct spi_imx_data* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int
spi_imx_unprepare_message(struct spi_master *master, struct spi_message *msg)
{
	struct spi_imx_data *spi_imx = spi_master_get_devdata(master);

	clk_disable(spi_imx->clk_ipg);
	clk_disable(spi_imx->clk_per);
	return 0;
}