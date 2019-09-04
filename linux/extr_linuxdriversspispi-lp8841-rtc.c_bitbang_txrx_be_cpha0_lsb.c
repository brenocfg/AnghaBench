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
struct spi_lp8841_rtc {int dummy; } ;

/* Variables and functions */
 unsigned int SPI_MASTER_NO_RX ; 
 unsigned int SPI_MASTER_NO_TX ; 
 int getmiso (struct spi_lp8841_rtc*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  setmosi (struct spi_lp8841_rtc*,int) ; 
 int /*<<< orphan*/  setsck (struct spi_lp8841_rtc*,unsigned int) ; 
 int /*<<< orphan*/  usleep_range (unsigned int,unsigned int) ; 

__attribute__((used)) static inline u32
bitbang_txrx_be_cpha0_lsb(struct spi_lp8841_rtc *data,
		unsigned usecs, unsigned cpol, unsigned flags,
		u32 word, u8 bits)
{
	/* if (cpol == 0) this is SPI_MODE_0; else this is SPI_MODE_2 */

	u32 shift = 32 - bits;
	/* clock starts at inactive polarity */
	for (; likely(bits); bits--) {

		/* setup LSB (to slave) on leading edge */
		if ((flags & SPI_MASTER_NO_TX) == 0)
			setmosi(data, (word & 1));

		usleep_range(usecs, usecs + 1);	/* T(setup) */

		/* sample LSB (from slave) on trailing edge */
		word >>= 1;
		if ((flags & SPI_MASTER_NO_RX) == 0)
			word |= (getmiso(data) << 31);

		setsck(data, !cpol);
		usleep_range(usecs, usecs + 1);

		setsck(data, cpol);
	}

	word >>= shift;
	return word;
}