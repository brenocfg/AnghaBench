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
typedef  int u16 ;
struct spi_device {int mode; int /*<<< orphan*/  cs_gpio; int /*<<< orphan*/  master; struct mpc512x_psc_spi_cs* controller_state; } ;
struct mpc512x_psc_spi_cs {int speed_hz; int /*<<< orphan*/  bits_per_word; } ;
struct mpc512x_psc_spi {int mclk_rate; int /*<<< orphan*/  (* cs_control ) (struct spi_device*,int) ;int /*<<< orphan*/  bits_per_word; } ;

/* Variables and functions */
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int SPI_LSB_FIRST ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int in_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  psc_addr (struct mpc512x_psc_spi*,int) ; 
 struct mpc512x_psc_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct spi_device*,int) ; 

__attribute__((used)) static void mpc512x_psc_spi_activate_cs(struct spi_device *spi)
{
	struct mpc512x_psc_spi_cs *cs = spi->controller_state;
	struct mpc512x_psc_spi *mps = spi_master_get_devdata(spi->master);
	u32 sicr;
	u32 ccr;
	int speed;
	u16 bclkdiv;

	sicr = in_be32(psc_addr(mps, sicr));

	/* Set clock phase and polarity */
	if (spi->mode & SPI_CPHA)
		sicr |= 0x00001000;
	else
		sicr &= ~0x00001000;

	if (spi->mode & SPI_CPOL)
		sicr |= 0x00002000;
	else
		sicr &= ~0x00002000;

	if (spi->mode & SPI_LSB_FIRST)
		sicr |= 0x10000000;
	else
		sicr &= ~0x10000000;
	out_be32(psc_addr(mps, sicr), sicr);

	ccr = in_be32(psc_addr(mps, ccr));
	ccr &= 0xFF000000;
	speed = cs->speed_hz;
	if (!speed)
		speed = 1000000;	/* default 1MHz */
	bclkdiv = (mps->mclk_rate / speed) - 1;

	ccr |= (((bclkdiv & 0xff) << 16) | (((bclkdiv >> 8) & 0xff) << 8));
	out_be32(psc_addr(mps, ccr), ccr);
	mps->bits_per_word = cs->bits_per_word;

	if (mps->cs_control && gpio_is_valid(spi->cs_gpio))
		mps->cs_control(spi, (spi->mode & SPI_CS_HIGH) ? 1 : 0);
}