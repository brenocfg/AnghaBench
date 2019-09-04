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
struct spi_transfer {int bits_per_word; int speed_hz; } ;
struct spi_device {int bits_per_word; int max_speed_hz; struct spi_bitbang_cs* controller_state; } ;
struct spi_bitbang_cs {int nsecs; int /*<<< orphan*/  txrx_bufs; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_UDELAY_MS ; 
 int /*<<< orphan*/  bitbang_txrx_16 ; 
 int /*<<< orphan*/  bitbang_txrx_32 ; 
 int /*<<< orphan*/  bitbang_txrx_8 ; 

int spi_bitbang_setup_transfer(struct spi_device *spi, struct spi_transfer *t)
{
	struct spi_bitbang_cs	*cs = spi->controller_state;
	u8			bits_per_word;
	u32			hz;

	if (t) {
		bits_per_word = t->bits_per_word;
		hz = t->speed_hz;
	} else {
		bits_per_word = 0;
		hz = 0;
	}

	/* spi_transfer level calls that work per-word */
	if (!bits_per_word)
		bits_per_word = spi->bits_per_word;
	if (bits_per_word <= 8)
		cs->txrx_bufs = bitbang_txrx_8;
	else if (bits_per_word <= 16)
		cs->txrx_bufs = bitbang_txrx_16;
	else if (bits_per_word <= 32)
		cs->txrx_bufs = bitbang_txrx_32;
	else
		return -EINVAL;

	/* nsecs = (clock period)/2 */
	if (!hz)
		hz = spi->max_speed_hz;
	if (hz) {
		cs->nsecs = (1000000000/2) / hz;
		if (cs->nsecs > (MAX_UDELAY_MS * 1000 * 1000))
			return -EINVAL;
	}

	return 0;
}