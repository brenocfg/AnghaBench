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
typedef  int u32 ;
struct spi_device {int dummy; } ;
struct ath79_spi {int ioc_base; } ;

/* Variables and functions */
 int AR71XX_SPI_IOC_CLK ; 
 int AR71XX_SPI_IOC_DO ; 
 int /*<<< orphan*/  AR71XX_SPI_REG_IOC ; 
 int /*<<< orphan*/  AR71XX_SPI_REG_RDS ; 
 int /*<<< orphan*/  ath79_spi_delay (struct ath79_spi*,unsigned int) ; 
 int ath79_spi_rr (struct ath79_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath79_spi_wr (struct ath79_spi*,int /*<<< orphan*/ ,int) ; 
 struct ath79_spi* ath79_spidev_to_sp (struct spi_device*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static u32 ath79_spi_txrx_mode0(struct spi_device *spi, unsigned int nsecs,
			       u32 word, u8 bits, unsigned flags)
{
	struct ath79_spi *sp = ath79_spidev_to_sp(spi);
	u32 ioc = sp->ioc_base;

	/* clock starts at inactive polarity */
	for (word <<= (32 - bits); likely(bits); bits--) {
		u32 out;

		if (word & (1 << 31))
			out = ioc | AR71XX_SPI_IOC_DO;
		else
			out = ioc & ~AR71XX_SPI_IOC_DO;

		/* setup MSB (to slave) on trailing edge */
		ath79_spi_wr(sp, AR71XX_SPI_REG_IOC, out);
		ath79_spi_delay(sp, nsecs);
		ath79_spi_wr(sp, AR71XX_SPI_REG_IOC, out | AR71XX_SPI_IOC_CLK);
		ath79_spi_delay(sp, nsecs);
		if (bits == 1)
			ath79_spi_wr(sp, AR71XX_SPI_REG_IOC, out);

		word <<= 1;
	}

	return ath79_spi_rr(sp, AR71XX_SPI_REG_RDS);
}