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
typedef  int u16 ;
struct spi_transfer {int len; scalar_t__* tx_buf; } ;
struct spi_message {int dummy; } ;
struct adf7242_local {int /*<<< orphan*/  bmux; int /*<<< orphan*/  spi; scalar_t__* buf; } ;

/* Variables and functions */
 scalar_t__ CMD_SPI_PRAM_WR ; 
 int PRAM_PAGESIZE ; 
 int /*<<< orphan*/  REG_PRAMPG ; 
 int /*<<< orphan*/  adf7242_write_reg (struct adf7242_local*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static int adf7242_upload_firmware(struct adf7242_local *lp, u8 *data, u16 len)
{
	struct spi_message msg;
	struct spi_transfer xfer_buf = { };
	int status, i, page = 0;
	u8 *buf = lp->buf;

	struct spi_transfer xfer_head = {
		.len = 2,
		.tx_buf = buf,
	};

	buf[0] = CMD_SPI_PRAM_WR;
	buf[1] = 0;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer_head, &msg);
	spi_message_add_tail(&xfer_buf, &msg);

	for (i = len; i >= 0; i -= PRAM_PAGESIZE) {
		adf7242_write_reg(lp, REG_PRAMPG, page);

		xfer_buf.len = (i >= PRAM_PAGESIZE) ? PRAM_PAGESIZE : i;
		xfer_buf.tx_buf = &data[page * PRAM_PAGESIZE];

		mutex_lock(&lp->bmux);
		status = spi_sync(lp->spi, &msg);
		mutex_unlock(&lp->bmux);
		page++;
	}

	return status;
}