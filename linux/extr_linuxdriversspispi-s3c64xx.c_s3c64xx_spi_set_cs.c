#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct spi_device {int /*<<< orphan*/  master; } ;
struct s3c64xx_spi_driver_data {scalar_t__ regs; TYPE_2__* port_conf; TYPE_1__* cntrlr_info; } ;
struct TYPE_4__ {int quirks; } ;
struct TYPE_3__ {scalar_t__ no_cs; } ;

/* Variables and functions */
 int S3C64XX_SPI_QUIRK_CS_AUTO ; 
 int S3C64XX_SPI_SLAVE_AUTO ; 
 int S3C64XX_SPI_SLAVE_NSC_CNT_2 ; 
 scalar_t__ S3C64XX_SPI_SLAVE_SEL ; 
 int S3C64XX_SPI_SLAVE_SIG_INACT ; 
 int readl (scalar_t__) ; 
 struct s3c64xx_spi_driver_data* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void s3c64xx_spi_set_cs(struct spi_device *spi, bool enable)
{
	struct s3c64xx_spi_driver_data *sdd =
					spi_master_get_devdata(spi->master);

	if (sdd->cntrlr_info->no_cs)
		return;

	if (enable) {
		if (!(sdd->port_conf->quirks & S3C64XX_SPI_QUIRK_CS_AUTO)) {
			writel(0, sdd->regs + S3C64XX_SPI_SLAVE_SEL);
		} else {
			u32 ssel = readl(sdd->regs + S3C64XX_SPI_SLAVE_SEL);

			ssel |= (S3C64XX_SPI_SLAVE_AUTO |
						S3C64XX_SPI_SLAVE_NSC_CNT_2);
			writel(ssel, sdd->regs + S3C64XX_SPI_SLAVE_SEL);
		}
	} else {
		if (!(sdd->port_conf->quirks & S3C64XX_SPI_QUIRK_CS_AUTO))
			writel(S3C64XX_SPI_SLAVE_SIG_INACT,
			       sdd->regs + S3C64XX_SPI_SLAVE_SEL);
	}
}