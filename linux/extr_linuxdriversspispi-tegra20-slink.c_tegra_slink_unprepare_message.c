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
struct tegra_slink_data {int /*<<< orphan*/  def_command2_reg; int /*<<< orphan*/  def_command_reg; } ;
struct spi_message {int dummy; } ;
struct spi_master {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLINK_COMMAND ; 
 int /*<<< orphan*/  SLINK_COMMAND2 ; 
 struct tegra_slink_data* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  tegra_slink_writel (struct tegra_slink_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_slink_unprepare_message(struct spi_master *master,
					 struct spi_message *msg)
{
	struct tegra_slink_data *tspi = spi_master_get_devdata(master);

	tegra_slink_writel(tspi, tspi->def_command_reg, SLINK_COMMAND);
	tegra_slink_writel(tspi, tspi->def_command2_reg, SLINK_COMMAND2);

	return 0;
}