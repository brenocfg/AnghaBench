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
struct bcm2835aux_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_AUX_SPI_CNTL0 ; 
 int /*<<< orphan*/  BCM2835_AUX_SPI_CNTL0_CLEARFIFO ; 
 int /*<<< orphan*/  BCM2835_AUX_SPI_CNTL1 ; 
 int /*<<< orphan*/  bcm2835aux_wr (struct bcm2835aux_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm2835aux_spi_reset_hw(struct bcm2835aux_spi *bs)
{
	/* disable spi clearing fifo and interrupts */
	bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, 0);
	bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL0,
		      BCM2835_AUX_SPI_CNTL0_CLEARFIFO);
}