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
struct mt7621_spi {scalar_t__ pending_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT7621_SPI_MASTER ; 
 int mt7621_spi_read (struct mt7621_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7621_spi_write (struct mt7621_spi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mt7621_spi_reset(struct mt7621_spi *rs, int duplex)
{
	u32 master = mt7621_spi_read(rs, MT7621_SPI_MASTER);

	master |= 7 << 29;
	master |= 1 << 2;
	if (duplex)
		master |= 1 << 10;
	else
		master &= ~(1 << 10);

	mt7621_spi_write(rs, MT7621_SPI_MASTER, master);
	rs->pending_write = 0;
}