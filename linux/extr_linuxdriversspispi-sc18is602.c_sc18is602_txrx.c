#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spi_transfer {unsigned int len; int* tx_buf; int* rx_buf; } ;
struct spi_message {TYPE_1__* spi; } ;
struct sc18is602 {int tlen; int* buffer; int rindex; int /*<<< orphan*/  client; } ;
struct TYPE_2__ {int chip_select; } ;

/* Variables and functions */
 int EIO ; 
 int SC18IS602_BUFSIZ ; 
 int i2c_master_recv (int /*<<< orphan*/ ,int*,int) ; 
 int i2c_master_send (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,unsigned int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,unsigned int) ; 
 int sc18is602_wait_ready (struct sc18is602*,int) ; 

__attribute__((used)) static int sc18is602_txrx(struct sc18is602 *hw, struct spi_message *msg,
			  struct spi_transfer *t, bool do_transfer)
{
	unsigned int len = t->len;
	int ret;

	if (hw->tlen == 0) {
		/* First byte (I2C command) is chip select */
		hw->buffer[0] = 1 << msg->spi->chip_select;
		hw->tlen = 1;
		hw->rindex = 0;
	}
	/*
	 * We can not immediately send data to the chip, since each I2C message
	 * resembles a full SPI message (from CS active to CS inactive).
	 * Enqueue messages up to the first read or until do_transfer is true.
	 */
	if (t->tx_buf) {
		memcpy(&hw->buffer[hw->tlen], t->tx_buf, len);
		hw->tlen += len;
		if (t->rx_buf)
			do_transfer = true;
		else
			hw->rindex = hw->tlen - 1;
	} else if (t->rx_buf) {
		/*
		 * For receive-only transfers we still need to perform a dummy
		 * write to receive data from the SPI chip.
		 * Read data starts at the end of transmit data (minus 1 to
		 * account for CS).
		 */
		hw->rindex = hw->tlen - 1;
		memset(&hw->buffer[hw->tlen], 0, len);
		hw->tlen += len;
		do_transfer = true;
	}

	if (do_transfer && hw->tlen > 1) {
		ret = sc18is602_wait_ready(hw, SC18IS602_BUFSIZ);
		if (ret < 0)
			return ret;
		ret = i2c_master_send(hw->client, hw->buffer, hw->tlen);
		if (ret < 0)
			return ret;
		if (ret != hw->tlen)
			return -EIO;

		if (t->rx_buf) {
			int rlen = hw->rindex + len;

			ret = sc18is602_wait_ready(hw, hw->tlen);
			if (ret < 0)
				return ret;
			ret = i2c_master_recv(hw->client, hw->buffer, rlen);
			if (ret < 0)
				return ret;
			if (ret != rlen)
				return -EIO;
			memcpy(t->rx_buf, &hw->buffer[hw->rindex], len);
		}
		hw->tlen = 0;
	}
	return len;
}