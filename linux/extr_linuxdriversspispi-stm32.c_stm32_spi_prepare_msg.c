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
typedef  int u32 ;
struct stm32_spi {int /*<<< orphan*/  lock; scalar_t__ base; int /*<<< orphan*/  dev; scalar_t__ cur_midi; } ;
struct spi_message {struct spi_device* spi; } ;
struct spi_master {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct spi_device {int mode; TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int SPI_CFG2_CPHA ; 
 int SPI_CFG2_CPOL ; 
 int SPI_CFG2_LSBFRST ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int SPI_LSB_FIRST ; 
 scalar_t__ STM32_SPI_CFG2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 int readl_relaxed (scalar_t__) ; 
 struct stm32_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int stm32_spi_prepare_msg(struct spi_master *master,
				 struct spi_message *msg)
{
	struct stm32_spi *spi = spi_master_get_devdata(master);
	struct spi_device *spi_dev = msg->spi;
	struct device_node *np = spi_dev->dev.of_node;
	unsigned long flags;
	u32 cfg2_clrb = 0, cfg2_setb = 0;

	/* SPI slave device may need time between data frames */
	spi->cur_midi = 0;
	if (np && !of_property_read_u32(np, "st,spi-midi-ns", &spi->cur_midi))
		dev_dbg(spi->dev, "%dns inter-data idleness\n", spi->cur_midi);

	if (spi_dev->mode & SPI_CPOL)
		cfg2_setb |= SPI_CFG2_CPOL;
	else
		cfg2_clrb |= SPI_CFG2_CPOL;

	if (spi_dev->mode & SPI_CPHA)
		cfg2_setb |= SPI_CFG2_CPHA;
	else
		cfg2_clrb |= SPI_CFG2_CPHA;

	if (spi_dev->mode & SPI_LSB_FIRST)
		cfg2_setb |= SPI_CFG2_LSBFRST;
	else
		cfg2_clrb |= SPI_CFG2_LSBFRST;

	dev_dbg(spi->dev, "cpol=%d cpha=%d lsb_first=%d cs_high=%d\n",
		spi_dev->mode & SPI_CPOL,
		spi_dev->mode & SPI_CPHA,
		spi_dev->mode & SPI_LSB_FIRST,
		spi_dev->mode & SPI_CS_HIGH);

	spin_lock_irqsave(&spi->lock, flags);

	if (cfg2_clrb || cfg2_setb)
		writel_relaxed(
			(readl_relaxed(spi->base + STM32_SPI_CFG2) &
				~cfg2_clrb) | cfg2_setb,
			       spi->base + STM32_SPI_CFG2);

	spin_unlock_irqrestore(&spi->lock, flags);

	return 0;
}