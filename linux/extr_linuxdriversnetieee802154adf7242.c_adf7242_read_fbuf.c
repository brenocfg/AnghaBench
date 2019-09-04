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
typedef  scalar_t__ u8 ;
struct spi_transfer {int len; scalar_t__* rx_buf; scalar_t__* tx_buf; } ;
struct spi_message {int dummy; } ;
struct adf7242_local {int /*<<< orphan*/  bmux; int /*<<< orphan*/  spi; scalar_t__* buf; } ;

/* Variables and functions */
 scalar_t__ CMD_SPI_NOP ; 
 scalar_t__ CMD_SPI_PKT_RD ; 
 scalar_t__ CMD_SPI_PRAM_RD ; 
 int /*<<< orphan*/  adf7242_wait_spi_ready (struct adf7242_local*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static int adf7242_read_fbuf(struct adf7242_local *lp,
			     u8 *data, size_t len, bool packet_read)
{
	u8 *buf = lp->buf;
	int status;
	struct spi_message msg;
	struct spi_transfer xfer_head = {
		.len = 3,
		.tx_buf = buf,
		.rx_buf = buf,
	};
	struct spi_transfer xfer_buf = {
		.len = len,
		.rx_buf = data,
	};

	spi_message_init(&msg);
	spi_message_add_tail(&xfer_head, &msg);
	spi_message_add_tail(&xfer_buf, &msg);

	adf7242_wait_spi_ready(lp, __LINE__);

	mutex_lock(&lp->bmux);
	if (packet_read) {
		buf[0] = CMD_SPI_PKT_RD;
		buf[1] = CMD_SPI_NOP;
		buf[2] = 0;	/* PHR */
	} else {
		buf[0] = CMD_SPI_PRAM_RD;
		buf[1] = 0;
		buf[2] = CMD_SPI_NOP;
	}

	status = spi_sync(lp->spi, &msg);

	mutex_unlock(&lp->bmux);

	return status;
}