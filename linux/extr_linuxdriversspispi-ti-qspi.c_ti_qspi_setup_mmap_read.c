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
typedef  int u8 ;
typedef  int u32 ;
struct ti_qspi {int dummy; } ;
struct spi_device {int /*<<< orphan*/  chip_select; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int QSPI_SETUP_ADDR_SHIFT ; 
 int QSPI_SETUP_DUMMY_SHIFT ; 
 int QSPI_SETUP_RD_DUAL ; 
 int QSPI_SETUP_RD_NORMAL ; 
 int QSPI_SETUP_RD_QUAD ; 
 int /*<<< orphan*/  QSPI_SPI_SETUP_REG (int /*<<< orphan*/ ) ; 
#define  SPI_NBITS_DUAL 129 
#define  SPI_NBITS_QUAD 128 
 struct ti_qspi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_qspi_write (struct ti_qspi*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ti_qspi_setup_mmap_read(struct spi_device *spi, u8 opcode,
				    u8 data_nbits, u8 addr_width,
				    u8 dummy_bytes)
{
	struct ti_qspi  *qspi = spi_master_get_devdata(spi->master);
	u32 memval = opcode;

	switch (data_nbits) {
	case SPI_NBITS_QUAD:
		memval |= QSPI_SETUP_RD_QUAD;
		break;
	case SPI_NBITS_DUAL:
		memval |= QSPI_SETUP_RD_DUAL;
		break;
	default:
		memval |= QSPI_SETUP_RD_NORMAL;
		break;
	}
	memval |= ((addr_width - 1) << QSPI_SETUP_ADDR_SHIFT |
		   dummy_bytes << QSPI_SETUP_DUMMY_SHIFT);
	ti_qspi_write(qspi, memval,
		      QSPI_SPI_SETUP_REG(spi->chip_select));
}