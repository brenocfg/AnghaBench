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
struct spi_transfer {int len; int speed_hz; int delay_usecs; struct spi_transfer* rx_buf; struct spi_transfer const* tx_buf; } ;
typedef  struct spi_transfer uint8_t ;
typedef  int /*<<< orphan*/  transfer ;
struct spi_message {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pisnd_spi_device ; 
 int /*<<< orphan*/  pisnd_spi_has_more () ; 
 int /*<<< orphan*/  printd (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printe (char*,...) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 
 int /*<<< orphan*/  spilock ; 
 int /*<<< orphan*/  spilockflags ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spi_transfer(const uint8_t *txbuf, uint8_t *rxbuf, int len)
{
	int err;
	struct spi_transfer transfer;
	struct spi_message msg;

	memset(rxbuf, 0, len);

	if (!pisnd_spi_device) {
		printe("pisnd_spi_device null, returning\n");
		return;
	}

	spi_message_init(&msg);

	memset(&transfer, 0, sizeof(transfer));

	transfer.tx_buf = txbuf;
	transfer.rx_buf = rxbuf;
	transfer.len = len;
	transfer.speed_hz = 100000;
	transfer.delay_usecs = 10;
	spi_message_add_tail(&transfer, &msg);

	spin_lock_irqsave(&spilock, spilockflags);
	err = spi_sync(pisnd_spi_device, &msg);
	spin_unlock_irqrestore(&spilock, spilockflags);

	if (err < 0) {
		printe("spi_sync error %d\n", err);
		return;
	}

	printd("hasMore %d\n", pisnd_spi_has_more());
}