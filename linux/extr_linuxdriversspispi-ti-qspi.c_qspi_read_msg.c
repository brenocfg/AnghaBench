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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ti_qspi {unsigned int cmd; scalar_t__ base; int /*<<< orphan*/  dev; int /*<<< orphan*/  dc; } ;
struct spi_transfer {int rx_nbits; int bits_per_word; int /*<<< orphan*/ * rx_buf; } ;

/* Variables and functions */
 int EBUSY ; 
 int ETIMEDOUT ; 
 unsigned int QSPI_RD_DUAL ; 
 unsigned int QSPI_RD_QUAD ; 
 unsigned int QSPI_RD_SNGL ; 
 int /*<<< orphan*/  QSPI_SPI_CMD_REG ; 
 scalar_t__ QSPI_SPI_DATA_REG ; 
#define  SPI_NBITS_DUAL 129 
#define  SPI_NBITS_QUAD 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ qspi_is_busy (struct ti_qspi*) ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 
 scalar_t__ ti_qspi_poll_wc (struct ti_qspi*) ; 
 int /*<<< orphan*/  ti_qspi_write (struct ti_qspi*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qspi_read_msg(struct ti_qspi *qspi, struct spi_transfer *t,
			 int count)
{
	int wlen;
	unsigned int cmd;
	u8 *rxbuf;

	rxbuf = t->rx_buf;
	cmd = qspi->cmd;
	switch (t->rx_nbits) {
	case SPI_NBITS_DUAL:
		cmd |= QSPI_RD_DUAL;
		break;
	case SPI_NBITS_QUAD:
		cmd |= QSPI_RD_QUAD;
		break;
	default:
		cmd |= QSPI_RD_SNGL;
		break;
	}
	wlen = t->bits_per_word >> 3;	/* in bytes */

	while (count) {
		dev_dbg(qspi->dev, "rx cmd %08x dc %08x\n", cmd, qspi->dc);
		if (qspi_is_busy(qspi))
			return -EBUSY;

		ti_qspi_write(qspi, cmd, QSPI_SPI_CMD_REG);
		if (ti_qspi_poll_wc(qspi)) {
			dev_err(qspi->dev, "read timed out\n");
			return -ETIMEDOUT;
		}
		switch (wlen) {
		case 1:
			*rxbuf = readb(qspi->base + QSPI_SPI_DATA_REG);
			break;
		case 2:
			*((u16 *)rxbuf) = readw(qspi->base + QSPI_SPI_DATA_REG);
			break;
		case 4:
			*((u32 *)rxbuf) = readl(qspi->base + QSPI_SPI_DATA_REG);
			break;
		}
		rxbuf += wlen;
		count -= wlen;
	}

	return 0;
}