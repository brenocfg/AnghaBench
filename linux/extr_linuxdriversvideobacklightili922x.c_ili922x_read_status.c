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
typedef  unsigned char u16 ;
struct spi_transfer {unsigned char* tx_buf; unsigned char* rx_buf; int cs_change; int bits_per_word; int len; } ;
struct spi_message {int dummy; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FREQ_REG (struct spi_device*,struct spi_transfer*) ; 
 int CMD_BUFSIZE ; 
 int /*<<< orphan*/  START_BYTE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_RS_INDEX ; 
 int /*<<< orphan*/  START_RW_READ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ili922x_id ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 unsigned char set_tx_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (struct spi_device*,struct spi_message*) ; 

__attribute__((used)) static int ili922x_read_status(struct spi_device *spi, u16 *rs)
{
	struct spi_message msg;
	struct spi_transfer xfer;
	unsigned char tbuf[CMD_BUFSIZE];
	unsigned char rbuf[CMD_BUFSIZE];
	int ret, i;

	memset(&xfer, 0, sizeof(struct spi_transfer));
	spi_message_init(&msg);
	xfer.tx_buf = tbuf;
	xfer.rx_buf = rbuf;
	xfer.cs_change = 1;
	CHECK_FREQ_REG(spi, &xfer);

	tbuf[0] = set_tx_byte(START_BYTE(ili922x_id, START_RS_INDEX,
					 START_RW_READ));
	/*
	 * we need 4-byte xfer here due to invalid dummy byte
	 * received after start byte
	 */
	for (i = 1; i < 4; i++)
		tbuf[i] = set_tx_byte(0);	/* dummy */

	xfer.bits_per_word = 8;
	xfer.len = 4;
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(spi, &msg);
	if (ret < 0) {
		dev_dbg(&spi->dev, "Error sending SPI message 0x%x", ret);
		return ret;
	}

	*rs = (rbuf[2] << 8) + rbuf[3];
	return 0;
}