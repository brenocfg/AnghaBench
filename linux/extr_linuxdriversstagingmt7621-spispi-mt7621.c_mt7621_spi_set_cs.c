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
struct spi_device {int chip_select; } ;
struct mt7621_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  MT7621_SPI_POLAR ; 
 int /*<<< orphan*/  mt7621_spi_reset (struct mt7621_spi*,int) ; 
 int /*<<< orphan*/  mt7621_spi_write (struct mt7621_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mt7621_spi* spidev_to_mt7621_spi (struct spi_device*) ; 

__attribute__((used)) static void mt7621_spi_set_cs(struct spi_device *spi, int enable)
{
	struct mt7621_spi *rs = spidev_to_mt7621_spi(spi);
	int cs = spi->chip_select;
	u32 polar = 0;

	mt7621_spi_reset(rs, cs);
	if (enable)
		polar = BIT(cs);
	mt7621_spi_write(rs, MT7621_SPI_POLAR, polar);
}