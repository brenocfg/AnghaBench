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
struct spi_transfer {int cs_change; int /*<<< orphan*/  speed_hz; int /*<<< orphan*/  delay_usecs; scalar_t__ len; struct spi_transfer* tx_buf; } ;
struct spi_message {int dummy; } ;
struct sk_buff {scalar_t__ len; struct spi_transfer* data; } ;
struct nci_spi {int /*<<< orphan*/  spi; int /*<<< orphan*/  xfer_speed_hz; int /*<<< orphan*/  xfer_udelay; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static int __nci_spi_send(struct nci_spi *nspi, struct sk_buff *skb,
			  int cs_change)
{
	struct spi_message m;
	struct spi_transfer t;

	memset(&t, 0, sizeof(struct spi_transfer));
	/* a NULL skb means we just want the SPI chip select line to raise */
	if (skb) {
		t.tx_buf = skb->data;
		t.len = skb->len;
	} else {
		/* still set tx_buf non NULL to make the driver happy */
		t.tx_buf = &t;
		t.len = 0;
	}
	t.cs_change = cs_change;
	t.delay_usecs = nspi->xfer_udelay;
	t.speed_hz = nspi->xfer_speed_hz;

	spi_message_init(&m);
	spi_message_add_tail(&t, &m);

	return spi_sync(nspi->spi, &m);
}