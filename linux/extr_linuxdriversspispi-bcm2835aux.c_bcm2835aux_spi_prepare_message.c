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
struct spi_message {struct spi_device* spi; } ;
struct spi_master {int dummy; } ;
struct spi_device {int mode; } ;
struct bcm2835aux_spi {int* cntl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_AUX_SPI_CNTL0 ; 
 int BCM2835_AUX_SPI_CNTL0_CPOL ; 
 int BCM2835_AUX_SPI_CNTL0_ENABLE ; 
 int BCM2835_AUX_SPI_CNTL0_IN_RISING ; 
 int BCM2835_AUX_SPI_CNTL0_MSBF_OUT ; 
 int BCM2835_AUX_SPI_CNTL0_OUT_RISING ; 
 int BCM2835_AUX_SPI_CNTL0_VAR_WIDTH ; 
 int /*<<< orphan*/  BCM2835_AUX_SPI_CNTL1 ; 
 int BCM2835_AUX_SPI_CNTL1_MSBF_IN ; 
 int SPI_CPOL ; 
 int /*<<< orphan*/  bcm2835aux_wr (struct bcm2835aux_spi*,int /*<<< orphan*/ ,int) ; 
 struct bcm2835aux_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int bcm2835aux_spi_prepare_message(struct spi_master *master,
					  struct spi_message *msg)
{
	struct spi_device *spi = msg->spi;
	struct bcm2835aux_spi *bs = spi_master_get_devdata(master);

	bs->cntl[0] = BCM2835_AUX_SPI_CNTL0_ENABLE |
		      BCM2835_AUX_SPI_CNTL0_VAR_WIDTH |
		      BCM2835_AUX_SPI_CNTL0_MSBF_OUT;
	bs->cntl[1] = BCM2835_AUX_SPI_CNTL1_MSBF_IN;

	/* handle all the modes */
	if (spi->mode & SPI_CPOL) {
		bs->cntl[0] |= BCM2835_AUX_SPI_CNTL0_CPOL;
		bs->cntl[0] |= BCM2835_AUX_SPI_CNTL0_OUT_RISING;
	} else {
		bs->cntl[0] |= BCM2835_AUX_SPI_CNTL0_IN_RISING;
	}
	bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL1, bs->cntl[1]);
	bcm2835aux_wr(bs, BCM2835_AUX_SPI_CNTL0, bs->cntl[0]);

	return 0;
}