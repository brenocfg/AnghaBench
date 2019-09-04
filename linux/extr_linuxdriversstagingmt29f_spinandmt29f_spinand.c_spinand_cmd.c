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
typedef  int /*<<< orphan*/  x ;
typedef  int u8 ;
struct spinand_cmd {int cmd; int n_addr; int* addr; int n_dummy; int n_tx; int* tx_buf; int n_rx; int /*<<< orphan*/  rx_buf; } ;
struct spi_transfer {int len; int* tx_buf; int /*<<< orphan*/  rx_buf; } ;
struct spi_message {int dummy; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (struct spi_device*,struct spi_message*) ; 

__attribute__((used)) static int spinand_cmd(struct spi_device *spi, struct spinand_cmd *cmd)
{
	struct spi_message message;
	struct spi_transfer x[4];
	u8 dummy = 0xff;

	spi_message_init(&message);
	memset(x, 0, sizeof(x));

	x[0].len = 1;
	x[0].tx_buf = &cmd->cmd;
	spi_message_add_tail(&x[0], &message);

	if (cmd->n_addr) {
		x[1].len = cmd->n_addr;
		x[1].tx_buf = cmd->addr;
		spi_message_add_tail(&x[1], &message);
	}

	if (cmd->n_dummy) {
		x[2].len = cmd->n_dummy;
		x[2].tx_buf = &dummy;
		spi_message_add_tail(&x[2], &message);
	}

	if (cmd->n_tx) {
		x[3].len = cmd->n_tx;
		x[3].tx_buf = cmd->tx_buf;
		spi_message_add_tail(&x[3], &message);
	}

	if (cmd->n_rx) {
		x[3].len = cmd->n_rx;
		x[3].rx_buf = cmd->rx_buf;
		spi_message_add_tail(&x[3], &message);
	}

	return spi_sync(spi, &message);
}