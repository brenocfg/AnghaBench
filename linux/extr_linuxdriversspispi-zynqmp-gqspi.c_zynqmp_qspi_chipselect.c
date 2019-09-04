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
typedef  scalar_t__ ulong ;
typedef  int u32 ;
struct zynqmp_qspi {int genfifobus; int genfifocs; int /*<<< orphan*/  dev; } ;
struct spi_device {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int GQSPI_CFG_START_GEN_FIFO_MASK ; 
 int /*<<< orphan*/  GQSPI_CONFIG_OFST ; 
 int GQSPI_GENFIFO_CS_HOLD ; 
 int GQSPI_GENFIFO_CS_SETUP ; 
 int GQSPI_GENFIFO_MODE_SPI ; 
 int /*<<< orphan*/  GQSPI_GEN_FIFO_OFST ; 
 int GQSPI_ISR_GENFIFOEMPTY_MASK ; 
 int /*<<< orphan*/  GQSPI_ISR_OFST ; 
 int GQSPI_ISR_TXEMPTY_MASK ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 struct zynqmp_qspi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after_eq (scalar_t__,scalar_t__) ; 
 int zynqmp_gqspi_read (struct zynqmp_qspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynqmp_gqspi_write (struct zynqmp_qspi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void zynqmp_qspi_chipselect(struct spi_device *qspi, bool is_high)
{
	struct zynqmp_qspi *xqspi = spi_master_get_devdata(qspi->master);
	ulong timeout;
	u32 genfifoentry = 0x0, statusreg;

	genfifoentry |= GQSPI_GENFIFO_MODE_SPI;
	genfifoentry |= xqspi->genfifobus;

	if (!is_high) {
		genfifoentry |= xqspi->genfifocs;
		genfifoentry |= GQSPI_GENFIFO_CS_SETUP;
	} else {
		genfifoentry |= GQSPI_GENFIFO_CS_HOLD;
	}

	zynqmp_gqspi_write(xqspi, GQSPI_GEN_FIFO_OFST, genfifoentry);

	/* Dummy generic FIFO entry */
	zynqmp_gqspi_write(xqspi, GQSPI_GEN_FIFO_OFST, 0x0);

	/* Manually start the generic FIFO command */
	zynqmp_gqspi_write(xqspi, GQSPI_CONFIG_OFST,
			zynqmp_gqspi_read(xqspi, GQSPI_CONFIG_OFST) |
			GQSPI_CFG_START_GEN_FIFO_MASK);

	timeout = jiffies + msecs_to_jiffies(1000);

	/* Wait until the generic FIFO command is empty */
	do {
		statusreg = zynqmp_gqspi_read(xqspi, GQSPI_ISR_OFST);

		if ((statusreg & GQSPI_ISR_GENFIFOEMPTY_MASK) &&
			(statusreg & GQSPI_ISR_TXEMPTY_MASK))
			break;
		else
			cpu_relax();
	} while (!time_after_eq(jiffies, timeout));

	if (time_after_eq(jiffies, timeout))
		dev_err(xqspi->dev, "Chip select timed out\n");
}