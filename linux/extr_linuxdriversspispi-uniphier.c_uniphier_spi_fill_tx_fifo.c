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
typedef  int u32 ;
struct uniphier_spi_priv {scalar_t__ base; int /*<<< orphan*/  bits_per_word; int /*<<< orphan*/  tx_bytes; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FIELD_PREP (int,unsigned int) ; 
 scalar_t__ SSI_FC ; 
 int SSI_FC_RXFTH_MASK ; 
 int SSI_FC_TXFTH_MASK ; 
 int /*<<< orphan*/  SSI_FIFO_DEPTH ; 
 int /*<<< orphan*/  bytes_per_word (int /*<<< orphan*/ ) ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  uniphier_spi_send (struct uniphier_spi_priv*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void uniphier_spi_fill_tx_fifo(struct uniphier_spi_priv *priv)
{
	unsigned int tx_count;
	u32 val;

	tx_count = DIV_ROUND_UP(priv->tx_bytes,
				bytes_per_word(priv->bits_per_word));
	tx_count = min(tx_count, SSI_FIFO_DEPTH);

	/* set fifo threshold */
	val = readl(priv->base + SSI_FC);
	val &= ~(SSI_FC_TXFTH_MASK | SSI_FC_RXFTH_MASK);
	val |= FIELD_PREP(SSI_FC_TXFTH_MASK, tx_count);
	val |= FIELD_PREP(SSI_FC_RXFTH_MASK, tx_count);
	writel(val, priv->base + SSI_FC);

	while (tx_count--)
		uniphier_spi_send(priv);
}