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
struct uniphier_spi_priv {int tx_bytes; scalar_t__ base; int /*<<< orphan*/ * tx_buf; int /*<<< orphan*/  bits_per_word; } ;

/* Variables and functions */
 scalar_t__ SSI_TXDR ; 
 int /*<<< orphan*/  bytes_per_word (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void uniphier_spi_send(struct uniphier_spi_priv *priv)
{
	int wsize;
	u32 val = 0;

	wsize = min(bytes_per_word(priv->bits_per_word), priv->tx_bytes);
	priv->tx_bytes -= wsize;

	if (priv->tx_buf) {
		switch (wsize) {
		case 1:
			val = *priv->tx_buf;
			break;
		case 2:
			val = get_unaligned_le16(priv->tx_buf);
			break;
		case 4:
			val = get_unaligned_le32(priv->tx_buf);
			break;
		}

		priv->tx_buf += wsize;
	}

	writel(val, priv->base + SSI_TXDR);
}