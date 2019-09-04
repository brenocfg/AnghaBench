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
struct spi_master {int bus_num; int num_chipselect; int /*<<< orphan*/  dev; int /*<<< orphan*/  transfer; int /*<<< orphan*/  setup; } ;
struct mmphw_ctrl {int /*<<< orphan*/  dev; void* reg_base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lcd_spi_one_transfer ; 
 int /*<<< orphan*/  lcd_spi_setup ; 
 struct spi_master* spi_alloc_master (int /*<<< orphan*/ ,int) ; 
 void** spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int spi_register_master (struct spi_master*) ; 

int lcd_spi_register(struct mmphw_ctrl *ctrl)
{
	struct spi_master *master;
	void **p_regbase;
	int err;

	master = spi_alloc_master(ctrl->dev, sizeof(void *));
	if (!master) {
		dev_err(ctrl->dev, "unable to allocate SPI master\n");
		return -ENOMEM;
	}
	p_regbase = spi_master_get_devdata(master);
	*p_regbase = ctrl->reg_base;

	/* set bus num to 5 to avoid conflict with other spi hosts */
	master->bus_num = 5;
	master->num_chipselect = 1;
	master->setup = lcd_spi_setup;
	master->transfer = lcd_spi_one_transfer;

	err = spi_register_master(master);
	if (err < 0) {
		dev_err(ctrl->dev, "unable to register SPI master\n");
		spi_master_put(master);
		return err;
	}

	dev_info(&master->dev, "registered\n");

	return 0;
}