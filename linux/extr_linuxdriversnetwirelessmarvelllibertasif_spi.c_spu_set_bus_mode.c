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
typedef  int u16 ;
struct if_spi_card {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IF_SPI_SPU_BUS_MODE_REG ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int spu_read_u16 (struct if_spi_card*,int /*<<< orphan*/ ,int*) ; 
 int spu_write_u16 (struct if_spi_card*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int spu_set_bus_mode(struct if_spi_card *card, u16 mode)
{
	int err = 0;
	u16 rval;
	/* set bus mode */
	err = spu_write_u16(card, IF_SPI_SPU_BUS_MODE_REG, mode);
	if (err)
		return err;
	/* Check that we were able to read back what we just wrote. */
	err = spu_read_u16(card, IF_SPI_SPU_BUS_MODE_REG, &rval);
	if (err)
		return err;
	if ((rval & 0xF) != mode) {
		pr_err("Can't read bus mode register\n");
		return -EIO;
	}
	return 0;
}