#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct spi_device {uintptr_t cs_gpio; int mode; scalar_t__ controller_data; TYPE_3__* master; } ;
struct sh_msiof_spi_priv {int native_cs_inited; int native_cs_high; TYPE_2__* pdev; int /*<<< orphan*/  master; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {struct device_node* of_node; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDR1_SYNCAC_SHIFT ; 
 int MDR1_SYNCMD_MASK ; 
 int MDR1_SYNCMD_SPI ; 
 int MDR1_TRMD ; 
 int /*<<< orphan*/  RMDR1 ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  TMDR1 ; 
 int TMDR1_PCON ; 
 int /*<<< orphan*/  gpio_direction_output (uintptr_t,int) ; 
 scalar_t__ gpio_is_valid (uintptr_t) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int sh_msiof_read (struct sh_msiof_spi_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_msiof_write (struct sh_msiof_spi_priv*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ spi_controller_is_slave (int /*<<< orphan*/ ) ; 
 struct sh_msiof_spi_priv* spi_master_get_devdata (TYPE_3__*) ; 

__attribute__((used)) static int sh_msiof_spi_setup(struct spi_device *spi)
{
	struct device_node	*np = spi->master->dev.of_node;
	struct sh_msiof_spi_priv *p = spi_master_get_devdata(spi->master);
	u32 clr, set, tmp;

	if (!np) {
		/*
		 * Use spi->controller_data for CS (same strategy as spi_gpio),
		 * if any. otherwise let HW control CS
		 */
		spi->cs_gpio = (uintptr_t)spi->controller_data;
	}

	if (gpio_is_valid(spi->cs_gpio)) {
		gpio_direction_output(spi->cs_gpio, !(spi->mode & SPI_CS_HIGH));
		return 0;
	}

	if (spi_controller_is_slave(p->master))
		return 0;

	if (p->native_cs_inited &&
	    (p->native_cs_high == !!(spi->mode & SPI_CS_HIGH)))
		return 0;

	/* Configure native chip select mode/polarity early */
	clr = MDR1_SYNCMD_MASK;
	set = MDR1_SYNCMD_SPI;
	if (spi->mode & SPI_CS_HIGH)
		clr |= BIT(MDR1_SYNCAC_SHIFT);
	else
		set |= BIT(MDR1_SYNCAC_SHIFT);
	pm_runtime_get_sync(&p->pdev->dev);
	tmp = sh_msiof_read(p, TMDR1) & ~clr;
	sh_msiof_write(p, TMDR1, tmp | set | MDR1_TRMD | TMDR1_PCON);
	tmp = sh_msiof_read(p, RMDR1) & ~clr;
	sh_msiof_write(p, RMDR1, tmp | set);
	pm_runtime_put(&p->pdev->dev);
	p->native_cs_high = spi->mode & SPI_CS_HIGH;
	p->native_cs_inited = true;
	return 0;
}