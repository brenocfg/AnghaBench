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
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS26522_E1TAF_ADDR ; 
 int DS26522_E1TAF_DEFAULT ; 
 int /*<<< orphan*/  DS26522_E1TNAF_ADDR ; 
 int DS26522_E1TNAF_DEFAULT ; 
 int /*<<< orphan*/  DS26522_LMCR_ADDR ; 
 int DS26522_LMCR_TE ; 
 int DS26522_LRISMR_75OHM ; 
 int /*<<< orphan*/  DS26522_LRISMR_ADDR ; 
 int DS26522_LRISMR_MAX ; 
 int /*<<< orphan*/  DS26522_LTITSR_ADDR ; 
 int DS26522_LTITSR_LBOS_75OHM ; 
 int DS26522_LTITSR_TLIS_75OHM ; 
 int /*<<< orphan*/  DS26522_LTRCR_ADDR ; 
 int DS26522_LTRCR_E1 ; 
 int /*<<< orphan*/  DS26522_RCR1_ADDR ; 
 int DS26522_RCR1_E1_CCS ; 
 int DS26522_RCR1_E1_HDB3 ; 
 int DS26522_RIOCR_2048KHZ ; 
 int /*<<< orphan*/  DS26522_RIOCR_ADDR ; 
 int DS26522_RIOCR_RSIO_OUT ; 
 int /*<<< orphan*/  DS26522_RMMR_ADDR ; 
 int DS26522_RMMR_E1 ; 
 int DS26522_RMMR_FRM_EN ; 
 int DS26522_RMMR_INIT_DONE ; 
 int /*<<< orphan*/  DS26522_TCR1_ADDR ; 
 int DS26522_TCR1_TB8ZS ; 
 int DS26522_TIOCR_2048KHZ ; 
 int /*<<< orphan*/  DS26522_TIOCR_ADDR ; 
 int DS26522_TIOCR_TSIO_OUT ; 
 int /*<<< orphan*/  DS26522_TMMR_ADDR ; 
 int DS26522_TMMR_E1 ; 
 int DS26522_TMMR_FRM_EN ; 
 int DS26522_TMMR_INIT_DONE ; 
 int slic_read (struct spi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slic_write (struct spi_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ds26522_e1_spec_config(struct spi_device *spi)
{
	/* Receive E1 Mode, Framer Disabled */
	slic_write(spi, DS26522_RMMR_ADDR, DS26522_RMMR_E1);

	/* Transmit E1 Mode, Framer Disable */
	slic_write(spi, DS26522_TMMR_ADDR, DS26522_TMMR_E1);

	/* Receive E1 Mode Framer Enable */
	slic_write(spi, DS26522_RMMR_ADDR,
		   slic_read(spi, DS26522_RMMR_ADDR) | DS26522_RMMR_FRM_EN);

	/* Transmit E1 Mode Framer Enable */
	slic_write(spi, DS26522_TMMR_ADDR,
		   slic_read(spi, DS26522_TMMR_ADDR) | DS26522_TMMR_FRM_EN);

	/* RCR1, receive E1 B8zs & ESF */
	slic_write(spi, DS26522_RCR1_ADDR,
		   DS26522_RCR1_E1_HDB3 | DS26522_RCR1_E1_CCS);

	/* RSYSCLK=2.048MHz, RSYNC-Output */
	slic_write(spi, DS26522_RIOCR_ADDR,
		   DS26522_RIOCR_2048KHZ | DS26522_RIOCR_RSIO_OUT);

	/* TCR1 Transmit E1 b8zs */
	slic_write(spi, DS26522_TCR1_ADDR, DS26522_TCR1_TB8ZS);

	/* TSYSCLK=2.048MHz, TSYNC-Output */
	slic_write(spi, DS26522_TIOCR_ADDR,
		   DS26522_TIOCR_2048KHZ | DS26522_TIOCR_TSIO_OUT);

	/* Set E1TAF */
	slic_write(spi, DS26522_E1TAF_ADDR, DS26522_E1TAF_DEFAULT);

	/* Set E1TNAF register */
	slic_write(spi, DS26522_E1TNAF_ADDR, DS26522_E1TNAF_DEFAULT);

	/* Receive E1 Mode Framer Enable & init Done */
	slic_write(spi, DS26522_RMMR_ADDR, slic_read(spi, DS26522_RMMR_ADDR) |
		   DS26522_RMMR_INIT_DONE);

	/* Transmit E1 Mode Framer Enable & init Done */
	slic_write(spi, DS26522_TMMR_ADDR, slic_read(spi, DS26522_TMMR_ADDR) |
		   DS26522_TMMR_INIT_DONE);

	/* Configure LIU E1 mode */
	slic_write(spi, DS26522_LTRCR_ADDR, DS26522_LTRCR_E1);

	/* E1 Mode default 75 ohm w/Transmit Impedance Matlinking */
	slic_write(spi, DS26522_LTITSR_ADDR,
		   DS26522_LTITSR_TLIS_75OHM | DS26522_LTITSR_LBOS_75OHM);

	/* E1 Mode default 75 ohm Long Haul w/Receive Impedance Matlinking */
	slic_write(spi, DS26522_LRISMR_ADDR,
		   DS26522_LRISMR_75OHM | DS26522_LRISMR_MAX);

	/* Enable Transmit output */
	slic_write(spi, DS26522_LMCR_ADDR, DS26522_LMCR_TE);
}