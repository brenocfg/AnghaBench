#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fsl_dspi {int /*<<< orphan*/  regmap; TYPE_1__* devtype_data; } ;
struct TYPE_2__ {scalar_t__ xspi_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_CTARE (int /*<<< orphan*/ ) ; 
 int SPI_CTARE_DTCP (int) ; 
 int SPI_CTARE_FMSZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MCR ; 
 int SPI_MCR_MASTER ; 
 int SPI_MCR_PCSIS ; 
 int SPI_MCR_XSPI ; 
 int /*<<< orphan*/  SPI_SR ; 
 int SPI_SR_CLEAR ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dspi_init(struct fsl_dspi *dspi)
{
	regmap_write(dspi->regmap, SPI_MCR, SPI_MCR_MASTER | SPI_MCR_PCSIS |
		     (dspi->devtype_data->xspi_mode ? SPI_MCR_XSPI : 0));
	regmap_write(dspi->regmap, SPI_SR, SPI_SR_CLEAR);
	if (dspi->devtype_data->xspi_mode)
		regmap_write(dspi->regmap, SPI_CTARE(0),
			     SPI_CTARE_FMSZE(0) | SPI_CTARE_DTCP(1));
}