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
typedef  int /*<<< orphan*/  u32 ;
struct uniphier_spi_priv {int rx_bytes; int /*<<< orphan*/ * rx_buf; scalar_t__ base; int /*<<< orphan*/  bits_per_word; } ;

/* Variables and functions */
 scalar_t__ SSI_RXDR ; 
 int /*<<< orphan*/  bytes_per_word (int /*<<< orphan*/ ) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static void uniphier_spi_recv(struct uniphier_spi_priv *priv)
{
	int rsize;
	u32 val;

	rsize = min(bytes_per_word(priv->bits_per_word), priv->rx_bytes);
	priv->rx_bytes -= rsize;

	val = readl(priv->base + SSI_RXDR);

	if (priv->rx_buf) {
		switch (rsize) {
		case 1:
			*priv->rx_buf = val;
			break;
		case 2:
			put_unaligned_le16(val, priv->rx_buf);
			break;
		case 4:
			put_unaligned_le32(val, priv->rx_buf);
			break;
		}

		priv->rx_buf += rsize;
	}
}