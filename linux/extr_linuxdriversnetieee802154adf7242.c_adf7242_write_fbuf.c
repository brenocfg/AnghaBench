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
struct spi_transfer {int len; int* tx_buf; } ;
struct spi_message {int dummy; } ;
struct adf7242_local {int* buf; int /*<<< orphan*/  bmux; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int CMD_SPI_PKT_WR ; 
 int /*<<< orphan*/  adf7242_wait_spi_ready (struct adf7242_local*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static int adf7242_write_fbuf(struct adf7242_local *lp, u8 *data, u8 len)
{
	u8 *buf = lp->buf;
	int status;
	struct spi_message msg;
	struct spi_transfer xfer_head = {
		.len = 2,
		.tx_buf = buf,

	};
	struct spi_transfer xfer_buf = {
		.len = len,
		.tx_buf = data,
	};

	spi_message_init(&msg);
	spi_message_add_tail(&xfer_head, &msg);
	spi_message_add_tail(&xfer_buf, &msg);

	adf7242_wait_spi_ready(lp, __LINE__);

	mutex_lock(&lp->bmux);
	buf[0] = CMD_SPI_PKT_WR;
	buf[1] = len + 2;

	status = spi_sync(lp->spi, &msg);
	mutex_unlock(&lp->bmux);

	return status;
}