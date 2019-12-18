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
typedef  void* u32 ;
struct spi_transfer {int* tx_buf; int* rx_buf; int len; scalar_t__ last_in_message_list; } ;
struct spi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  chip_select; } ;
struct cns3xxx_spi {int* tx; int* rx; int len; int /*<<< orphan*/  done; scalar_t__ last_in_message_list; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  cns3xxx_spi_tx_rx (struct cns3xxx_spi*,int /*<<< orphan*/ ,int,int,void**) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct cns3xxx_spi* to_hw (struct spi_device*) ; 

__attribute__((used)) static int cns3xxx_spi_txrx(struct spi_device *spi, struct spi_transfer *t)
{
	struct cns3xxx_spi *hw = to_hw(spi);

	dev_dbg(&spi->dev, "txrx: tx %p, rx %p, len %d\n", t->tx_buf, t->rx_buf,
		t->len);

	hw->tx = t->tx_buf;
	hw->rx = t->rx_buf;
	hw->len = t->len;
	hw->count = 0;
	hw->last_in_message_list = t->last_in_message_list;

	init_completion(&hw->done);

	if (hw->tx) {
		int i;
		u32 rx_data;
		for (i = 0; i < (hw->len - 1); i++) {
			dev_dbg(&spi->dev,
				"[SPI_CNS3XXX_DEBUG] hw->tx[%02d]: 0x%02x\n", i,
				hw->tx[i]);
			cns3xxx_spi_tx_rx(hw, spi->chip_select, 0, hw->tx[i],
					  &rx_data);
			if (hw->rx) {
				hw->rx[i] = rx_data;
				dev_dbg(&spi->dev,
					"[SPI_CNS3XXX_DEBUG] hw->rx[%02d]: 0x%02x\n",
					i, hw->rx[i]);
			}
		}

		if (t->last_in_message_list) {
			cns3xxx_spi_tx_rx(hw, spi->chip_select, 1, hw->tx[i],
					  &rx_data);
			if (hw->rx) {
				hw->rx[i] = rx_data;
				dev_dbg(&spi->dev,
					"[SPI_CNS3XXX_DEBUG] hw->rx[%02d]: 0x%02x\n",
					i, hw->rx[i]);
			}
		} else {
			cns3xxx_spi_tx_rx(hw, spi->chip_select, 0, hw->tx[i],
					  &rx_data);
		}
		goto done;
	}

	if (hw->rx) {
		int i;
		u32 rx_data;
		for (i = 0; i < (hw->len - 1); i++) {
			cns3xxx_spi_tx_rx(hw, spi->chip_select, 0, 0xff, &rx_data);
			hw->rx[i] = rx_data;
			dev_dbg(&spi->dev,
				"[SPI_CNS3XXX_DEBUG] hw->rx[%02d]: 0x%02x\n", i,
				hw->rx[i]);
		}

		if (t->last_in_message_list) {
			cns3xxx_spi_tx_rx(hw, spi->chip_select, 1, 0xff, &rx_data);
		} else {
			cns3xxx_spi_tx_rx(hw, spi->chip_select, 0, 0xff, &rx_data);
		}
		hw->rx[i] = rx_data;
		dev_dbg(&spi->dev, "[SPI_CNS3XXX_DEBUG] hw->rx[%02d]: 0x%02x\n",
			i, hw->rx[i]);
	}
done:
	return hw->len;
}