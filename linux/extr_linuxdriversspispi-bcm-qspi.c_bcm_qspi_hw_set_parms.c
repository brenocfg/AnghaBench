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
struct bcm_qspi_parms {int speed_hz; int bits_per_word; int mode; } ;
struct bcm_qspi {int base_clk; struct bcm_qspi_parms last_parms; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSPI ; 
 int MSPI_MASTER_BIT ; 
 int /*<<< orphan*/  MSPI_SPCR0_LSB ; 
 int /*<<< orphan*/  MSPI_SPCR0_MSB ; 
 int /*<<< orphan*/  QSPI_SPBR_MAX ; 
 int /*<<< orphan*/  QSPI_SPBR_MIN ; 
 int /*<<< orphan*/  bcm_qspi_write (struct bcm_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int clamp_val (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_qspi_hw_set_parms(struct bcm_qspi *qspi,
				  const struct bcm_qspi_parms *xp)
{
	u32 spcr, spbr = 0;

	if (xp->speed_hz)
		spbr = qspi->base_clk / (2 * xp->speed_hz);

	spcr = clamp_val(spbr, QSPI_SPBR_MIN, QSPI_SPBR_MAX);
	bcm_qspi_write(qspi, MSPI, MSPI_SPCR0_LSB, spcr);

	spcr = MSPI_MASTER_BIT;
	/* for 16 bit the data should be zero */
	if (xp->bits_per_word != 16)
		spcr |= xp->bits_per_word << 2;
	spcr |= xp->mode & 3;
	bcm_qspi_write(qspi, MSPI, MSPI_SPCR0_MSB, spcr);

	qspi->last_parms = *xp;
}