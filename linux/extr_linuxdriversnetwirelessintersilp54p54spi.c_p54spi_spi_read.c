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
typedef  int /*<<< orphan*/  t ;
struct spi_transfer {int len; void* rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct spi_message {int dummy; } ;
struct p54s_priv {int /*<<< orphan*/  spi; } ;
typedef  int /*<<< orphan*/  addr ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int SPI_ADRS_READ_BIT_15 ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int /*<<< orphan*/  spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static void p54spi_spi_read(struct p54s_priv *priv, u8 address,
			      void *buf, size_t len)
{
	struct spi_transfer t[2];
	struct spi_message m;
	__le16 addr;

	/* We first push the address */
	addr = cpu_to_le16(address << 8 | SPI_ADRS_READ_BIT_15);

	spi_message_init(&m);
	memset(t, 0, sizeof(t));

	t[0].tx_buf = &addr;
	t[0].len = sizeof(addr);
	spi_message_add_tail(&t[0], &m);

	t[1].rx_buf = buf;
	t[1].len = len;
	spi_message_add_tail(&t[1], &m);

	spi_sync(priv->spi, &m);
}