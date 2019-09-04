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
struct spi_device {int mode; int /*<<< orphan*/  dev; } ;
struct mt7621_spi {unsigned int speed; int /*<<< orphan*/  sys_freq; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,unsigned int) ; 
 int EINVAL ; 
 int MT7621_CPHA ; 
 int MT7621_CPOL ; 
 int MT7621_LSB_FIRST ; 
 int /*<<< orphan*/  MT7621_SPI_MASTER ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_LSB_FIRST ; 
#define  SPI_MODE_0 131 
#define  SPI_MODE_1 130 
#define  SPI_MODE_2 129 
#define  SPI_MODE_3 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int mt7621_spi_read (struct mt7621_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7621_spi_write (struct mt7621_spi*,int /*<<< orphan*/ ,int) ; 
 struct mt7621_spi* spidev_to_mt7621_spi (struct spi_device*) ; 

__attribute__((used)) static int mt7621_spi_prepare(struct spi_device *spi, unsigned int speed)
{
	struct mt7621_spi *rs = spidev_to_mt7621_spi(spi);
	u32 rate;
	u32 reg;

	dev_dbg(&spi->dev, "speed:%u\n", speed);

	rate = DIV_ROUND_UP(rs->sys_freq, speed);
	dev_dbg(&spi->dev, "rate-1:%u\n", rate);

	if (rate > 4097)
		return -EINVAL;

	if (rate < 2)
		rate = 2;

	reg = mt7621_spi_read(rs, MT7621_SPI_MASTER);
	reg &= ~(0xfff << 16);
	reg |= (rate - 2) << 16;
	rs->speed = speed;

	reg &= ~MT7621_LSB_FIRST;
	if (spi->mode & SPI_LSB_FIRST)
		reg |= MT7621_LSB_FIRST;

	reg &= ~(MT7621_CPHA | MT7621_CPOL);
	switch (spi->mode & (SPI_CPOL | SPI_CPHA)) {
	case SPI_MODE_0:
		break;
	case SPI_MODE_1:
		reg |= MT7621_CPHA;
		break;
	case SPI_MODE_2:
		reg |= MT7621_CPOL;
		break;
	case SPI_MODE_3:
		reg |= MT7621_CPOL | MT7621_CPHA;
		break;
	}
	mt7621_spi_write(rs, MT7621_SPI_MASTER, reg);

	return 0;
}