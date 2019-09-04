#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct spi_device {int chip_select; int /*<<< orphan*/  master; } ;
struct jcore_spi {unsigned int cs_reg; TYPE_2__* master; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  jcore_spi_program (struct jcore_spi*) ; 
 struct jcore_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jcore_spi_chipsel(struct spi_device *spi, bool value)
{
	struct jcore_spi *hw = spi_master_get_devdata(spi->master);
	u32 csbit = 1U << (2 * spi->chip_select);

	dev_dbg(hw->master->dev.parent, "chipselect %d\n", spi->chip_select);

	if (value)
		hw->cs_reg |= csbit;
	else
		hw->cs_reg &= ~csbit;

	jcore_spi_program(hw);
}