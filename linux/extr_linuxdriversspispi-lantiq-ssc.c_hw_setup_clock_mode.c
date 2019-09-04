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
struct lantiq_ssc_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTQ_SPI_CON ; 
 int LTQ_SPI_CON_HB ; 
 int LTQ_SPI_CON_IDLE ; 
 int LTQ_SPI_CON_LB ; 
 int LTQ_SPI_CON_PH ; 
 int LTQ_SPI_CON_PO ; 
 unsigned int SPI_CPHA ; 
 unsigned int SPI_CPOL ; 
 unsigned int SPI_LOOP ; 
 unsigned int SPI_LSB_FIRST ; 
 int /*<<< orphan*/  lantiq_ssc_maskl (struct lantiq_ssc_spi const*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hw_setup_clock_mode(const struct lantiq_ssc_spi *spi,
				unsigned int mode)
{
	u32 con_set = 0, con_clr = 0;

	/*
	 * SPI mode mapping in CON register:
	 * Mode CPOL CPHA CON.PO CON.PH
	 *  0    0    0      0      1
	 *  1    0    1      0      0
	 *  2    1    0      1      1
	 *  3    1    1      1      0
	 */
	if (mode & SPI_CPHA)
		con_clr |= LTQ_SPI_CON_PH;
	else
		con_set |= LTQ_SPI_CON_PH;

	if (mode & SPI_CPOL)
		con_set |= LTQ_SPI_CON_PO | LTQ_SPI_CON_IDLE;
	else
		con_clr |= LTQ_SPI_CON_PO | LTQ_SPI_CON_IDLE;

	/* Set heading control */
	if (mode & SPI_LSB_FIRST)
		con_clr |= LTQ_SPI_CON_HB;
	else
		con_set |= LTQ_SPI_CON_HB;

	/* Set loopback mode */
	if (mode & SPI_LOOP)
		con_set |= LTQ_SPI_CON_LB;
	else
		con_clr |= LTQ_SPI_CON_LB;

	lantiq_ssc_maskl(spi, con_clr, con_set, LTQ_SPI_CON);
}