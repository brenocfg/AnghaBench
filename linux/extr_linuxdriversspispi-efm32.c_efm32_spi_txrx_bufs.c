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
struct spi_transfer {int len; int /*<<< orphan*/  bits_per_word; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct spi_device {int /*<<< orphan*/  master; } ;
struct efm32_spi_ddata {int tx_len; int rx_len; int /*<<< orphan*/  lock; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  REG_IEN ; 
 int REG_IF_RXDATAV ; 
 int REG_IF_TXBL ; 
 int /*<<< orphan*/  efm32_spi_filltx (struct efm32_spi_ddata*) ; 
 int /*<<< orphan*/  efm32_spi_write32 (struct efm32_spi_ddata*,int,int /*<<< orphan*/ ) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 struct efm32_spi_ddata* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efm32_spi_txrx_bufs(struct spi_device *spi, struct spi_transfer *t)
{
	struct efm32_spi_ddata *ddata = spi_master_get_devdata(spi->master);
	int ret = -EBUSY;

	spin_lock_irq(&ddata->lock);

	if (ddata->tx_buf || ddata->rx_buf)
		goto out_unlock;

	ddata->tx_buf = t->tx_buf;
	ddata->rx_buf = t->rx_buf;
	ddata->tx_len = ddata->rx_len =
		t->len * DIV_ROUND_UP(t->bits_per_word, 8);

	efm32_spi_filltx(ddata);

	reinit_completion(&ddata->done);

	efm32_spi_write32(ddata, REG_IF_TXBL | REG_IF_RXDATAV, REG_IEN);

	spin_unlock_irq(&ddata->lock);

	wait_for_completion(&ddata->done);

	spin_lock_irq(&ddata->lock);

	ret = t->len - max(ddata->tx_len, ddata->rx_len);

	efm32_spi_write32(ddata, 0, REG_IEN);
	ddata->tx_buf = ddata->rx_buf = NULL;

out_unlock:
	spin_unlock_irq(&ddata->lock);

	return ret;
}