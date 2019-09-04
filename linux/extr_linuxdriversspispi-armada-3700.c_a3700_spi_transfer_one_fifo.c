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
typedef  int u32 ;
struct spi_transfer {int bits_per_word; unsigned int tx_nbits; unsigned int rx_nbits; scalar_t__ tx_buf; scalar_t__ rx_buf; } ;
struct spi_master {int dummy; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct a3700_spi {int buf_len; int xmit_data; scalar_t__ tx_buf; scalar_t__ rx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  A3700_SPI_DATA_OUT_REG ; 
 int /*<<< orphan*/  A3700_SPI_IF_CFG_REG ; 
 int /*<<< orphan*/  A3700_SPI_IF_DIN_CNT_REG ; 
 int /*<<< orphan*/  A3700_SPI_RFIFO_RDY ; 
 int A3700_SPI_RW_EN ; 
 int A3700_SPI_TIMEOUT ; 
 int /*<<< orphan*/  A3700_SPI_WFIFO_EMPTY ; 
 int /*<<< orphan*/  A3700_SPI_WFIFO_RDY ; 
 int /*<<< orphan*/  A3700_SPI_XFER_RDY ; 
 int A3700_SPI_XFER_START ; 
 int A3700_SPI_XFER_STOP ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  a3700_spi_fifo_flush (struct a3700_spi*) ; 
 int /*<<< orphan*/  a3700_spi_fifo_mode_set (struct a3700_spi*,int) ; 
 int a3700_spi_fifo_read (struct a3700_spi*) ; 
 int /*<<< orphan*/  a3700_spi_fifo_thres_set (struct a3700_spi*,unsigned int) ; 
 int a3700_spi_fifo_write (struct a3700_spi*) ; 
 int /*<<< orphan*/  a3700_spi_header_set (struct a3700_spi*) ; 
 int /*<<< orphan*/  a3700_spi_pin_mode_set (struct a3700_spi*,unsigned int,int) ; 
 int /*<<< orphan*/  a3700_spi_transfer_abort_fifo (struct a3700_spi*) ; 
 int /*<<< orphan*/  a3700_spi_transfer_wait (struct spi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (struct spi_master*) ; 
 struct a3700_spi* spi_master_get_devdata (struct spi_master*) ; 
 int spireg_read (struct a3700_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spireg_write (struct a3700_spi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int a3700_spi_transfer_one_fifo(struct spi_master *master,
				  struct spi_device *spi,
				  struct spi_transfer *xfer)
{
	struct a3700_spi *a3700_spi = spi_master_get_devdata(master);
	int ret = 0, timeout = A3700_SPI_TIMEOUT;
	unsigned int nbits = 0, byte_len;
	u32 val;

	/* Make sure we use FIFO mode */
	a3700_spi_fifo_mode_set(a3700_spi, true);

	/* Configure FIFO thresholds */
	byte_len = xfer->bits_per_word >> 3;
	a3700_spi_fifo_thres_set(a3700_spi, byte_len);

	if (xfer->tx_buf)
		nbits = xfer->tx_nbits;
	else if (xfer->rx_buf)
		nbits = xfer->rx_nbits;

	a3700_spi_pin_mode_set(a3700_spi, nbits, xfer->rx_buf ? true : false);

	/* Flush the FIFOs */
	a3700_spi_fifo_flush(a3700_spi);

	/* Transfer first bytes of data when buffer is not 4-byte aligned */
	a3700_spi_header_set(a3700_spi);

	if (xfer->rx_buf) {
		/* Clear WFIFO, since it's last 2 bytes are shifted out during
		 * a read operation
		 */
		spireg_write(a3700_spi, A3700_SPI_DATA_OUT_REG, 0);

		/* Set read data length */
		spireg_write(a3700_spi, A3700_SPI_IF_DIN_CNT_REG,
			     a3700_spi->buf_len);
		/* Start READ transfer */
		val = spireg_read(a3700_spi, A3700_SPI_IF_CFG_REG);
		val &= ~A3700_SPI_RW_EN;
		val |= A3700_SPI_XFER_START;
		spireg_write(a3700_spi, A3700_SPI_IF_CFG_REG, val);
	} else if (xfer->tx_buf) {
		/* Start Write transfer */
		val = spireg_read(a3700_spi, A3700_SPI_IF_CFG_REG);
		val |= (A3700_SPI_XFER_START | A3700_SPI_RW_EN);
		spireg_write(a3700_spi, A3700_SPI_IF_CFG_REG, val);

		/*
		 * If there are data to be written to the SPI device, xmit_data
		 * flag is set true; otherwise the instruction in SPI_INSTR does
		 * not require data to be written to the SPI device, then
		 * xmit_data flag is set false.
		 */
		a3700_spi->xmit_data = (a3700_spi->buf_len != 0);
	}

	while (a3700_spi->buf_len) {
		if (a3700_spi->tx_buf) {
			/* Wait wfifo ready */
			if (!a3700_spi_transfer_wait(spi,
						     A3700_SPI_WFIFO_RDY)) {
				dev_err(&spi->dev,
					"wait wfifo ready timed out\n");
				ret = -ETIMEDOUT;
				goto error;
			}
			/* Fill up the wfifo */
			ret = a3700_spi_fifo_write(a3700_spi);
			if (ret)
				goto error;
		} else if (a3700_spi->rx_buf) {
			/* Wait rfifo ready */
			if (!a3700_spi_transfer_wait(spi,
						     A3700_SPI_RFIFO_RDY)) {
				dev_err(&spi->dev,
					"wait rfifo ready timed out\n");
				ret = -ETIMEDOUT;
				goto error;
			}
			/* Drain out the rfifo */
			ret = a3700_spi_fifo_read(a3700_spi);
			if (ret)
				goto error;
		}
	}

	/*
	 * Stop a write transfer in fifo mode:
	 *	- wait all the bytes in wfifo to be shifted out
	 *	 - set XFER_STOP bit
	 *	- wait XFER_START bit clear
	 *	- clear XFER_STOP bit
	 * Stop a read transfer in fifo mode:
	 *	- the hardware is to reset the XFER_START bit
	 *	   after the number of bytes indicated in DIN_CNT
	 *	   register
	 *	- just wait XFER_START bit clear
	 */
	if (a3700_spi->tx_buf) {
		if (a3700_spi->xmit_data) {
			/*
			 * If there are data written to the SPI device, wait
			 * until SPI_WFIFO_EMPTY is 1 to wait for all data to
			 * transfer out of write FIFO.
			 */
			if (!a3700_spi_transfer_wait(spi,
						     A3700_SPI_WFIFO_EMPTY)) {
				dev_err(&spi->dev, "wait wfifo empty timed out\n");
				return -ETIMEDOUT;
			}
		}

		if (!a3700_spi_transfer_wait(spi, A3700_SPI_XFER_RDY)) {
			dev_err(&spi->dev, "wait xfer ready timed out\n");
			return -ETIMEDOUT;
		}

		val = spireg_read(a3700_spi, A3700_SPI_IF_CFG_REG);
		val |= A3700_SPI_XFER_STOP;
		spireg_write(a3700_spi, A3700_SPI_IF_CFG_REG, val);
	}

	while (--timeout) {
		val = spireg_read(a3700_spi, A3700_SPI_IF_CFG_REG);
		if (!(val & A3700_SPI_XFER_START))
			break;
		udelay(1);
	}

	if (timeout == 0) {
		dev_err(&spi->dev, "wait transfer start clear timed out\n");
		ret = -ETIMEDOUT;
		goto error;
	}

	val &= ~A3700_SPI_XFER_STOP;
	spireg_write(a3700_spi, A3700_SPI_IF_CFG_REG, val);
	goto out;

error:
	a3700_spi_transfer_abort_fifo(a3700_spi);
out:
	spi_finalize_current_transfer(master);

	return ret;
}