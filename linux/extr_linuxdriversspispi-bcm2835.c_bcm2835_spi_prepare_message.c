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
struct spi_message {struct spi_device* spi; } ;
struct spi_master {int dummy; } ;
struct spi_device {int mode; } ;
struct bcm2835_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_SPI_CS ; 
 int BCM2835_SPI_CS_CPHA ; 
 int BCM2835_SPI_CS_CPOL ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int bcm2835_rd (struct bcm2835_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_wr (struct bcm2835_spi*,int /*<<< orphan*/ ,int) ; 
 struct bcm2835_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int bcm2835_spi_prepare_message(struct spi_master *master,
				       struct spi_message *msg)
{
	struct spi_device *spi = msg->spi;
	struct bcm2835_spi *bs = spi_master_get_devdata(master);
	u32 cs = bcm2835_rd(bs, BCM2835_SPI_CS);

	cs &= ~(BCM2835_SPI_CS_CPOL | BCM2835_SPI_CS_CPHA);

	if (spi->mode & SPI_CPOL)
		cs |= BCM2835_SPI_CS_CPOL;
	if (spi->mode & SPI_CPHA)
		cs |= BCM2835_SPI_CS_CPHA;

	bcm2835_wr(bs, BCM2835_SPI_CS, cs);

	return 0;
}