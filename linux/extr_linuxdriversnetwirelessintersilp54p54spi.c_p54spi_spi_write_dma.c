#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct p54s_priv {TYPE_1__* spi; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  HOST_ALLOWED ; 
 int /*<<< orphan*/  SPI_ADRS_DMA_DATA ; 
 int /*<<< orphan*/  SPI_ADRS_DMA_WRITE_BASE ; 
 int /*<<< orphan*/  SPI_ADRS_DMA_WRITE_CTRL ; 
 int /*<<< orphan*/  SPI_ADRS_DMA_WRITE_LEN ; 
 size_t SPI_DMA_WRITE_CTRL_ENABLE ; 
 int /*<<< orphan*/  cpu_to_le16 (size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  p54spi_spi_write (struct p54s_priv*,int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  p54spi_wait_bit (struct p54s_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p54spi_write16 (struct p54s_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p54spi_write32 (struct p54s_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int p54spi_spi_write_dma(struct p54s_priv *priv, __le32 base,
				const void *buf, size_t len)
{
	if (!p54spi_wait_bit(priv, SPI_ADRS_DMA_WRITE_CTRL, HOST_ALLOWED)) {
		dev_err(&priv->spi->dev, "spi_write_dma not allowed "
			"to DMA write.\n");
		return -EAGAIN;
	}

	p54spi_write16(priv, SPI_ADRS_DMA_WRITE_CTRL,
		       cpu_to_le16(SPI_DMA_WRITE_CTRL_ENABLE));

	p54spi_write16(priv, SPI_ADRS_DMA_WRITE_LEN, cpu_to_le16(len));
	p54spi_write32(priv, SPI_ADRS_DMA_WRITE_BASE, base);
	p54spi_spi_write(priv, SPI_ADRS_DMA_DATA, buf, len);
	return 0;
}