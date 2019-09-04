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
struct xlp_spi_priv {int cmd_cont; } ;
struct spi_transfer {unsigned char* tx_buf; unsigned char* rx_buf; int len; } ;

/* Variables and functions */
 int XLP_SPI_XFER_SIZE ; 
 int xlp_spi_xfer_block (struct xlp_spi_priv*,unsigned char const*,unsigned char*,int,int) ; 

__attribute__((used)) static int xlp_spi_txrx_bufs(struct xlp_spi_priv *xs, struct spi_transfer *t)
{
	int bytesleft, sz;
	unsigned char *rx_buf;
	const unsigned char *tx_buf;

	tx_buf = t->tx_buf;
	rx_buf = t->rx_buf;
	bytesleft = t->len;
	while (bytesleft) {
		if (bytesleft > XLP_SPI_XFER_SIZE)
			sz = xlp_spi_xfer_block(xs, tx_buf, rx_buf,
					XLP_SPI_XFER_SIZE, 1);
		else
			sz = xlp_spi_xfer_block(xs, tx_buf, rx_buf,
					bytesleft, xs->cmd_cont);
		if (sz < 0)
			return sz;
		bytesleft -= sz;
		if (tx_buf)
			tx_buf += sz;
		if (rx_buf)
			rx_buf += sz;
	}
	return bytesleft;
}