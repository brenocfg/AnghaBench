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
struct spi_device {unsigned int chip_select; int mode; int /*<<< orphan*/  master; } ;
struct lantiq_ssc_spi {unsigned int base_cs; } ;

/* Variables and functions */
 unsigned int LTQ_SPI_FGPO_SETOUTN_S ; 
 int /*<<< orphan*/  LTQ_SPI_FPGO ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  lantiq_ssc_writel (struct lantiq_ssc_spi*,int,int /*<<< orphan*/ ) ; 
 struct lantiq_ssc_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lantiq_ssc_set_cs(struct spi_device *spidev, bool enable)
{
	struct lantiq_ssc_spi *spi = spi_master_get_devdata(spidev->master);
	unsigned int cs = spidev->chip_select;
	u32 fgpo;

	if (!!(spidev->mode & SPI_CS_HIGH) == enable)
		fgpo = (1 << (cs - spi->base_cs));
	else
		fgpo = (1 << (cs - spi->base_cs + LTQ_SPI_FGPO_SETOUTN_S));

	lantiq_ssc_writel(spi, fgpo, LTQ_SPI_FPGO);
}