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
struct spi_ppc4xx_cs {int /*<<< orphan*/  mode; } ;
struct spi_device {int mode; struct spi_ppc4xx_cs* controller_state; int /*<<< orphan*/  dev; int /*<<< orphan*/  max_speed_hz; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SPI_CLK_MODE0 ; 
 int /*<<< orphan*/  SPI_CLK_MODE1 ; 
 int /*<<< orphan*/  SPI_CLK_MODE2 ; 
 int /*<<< orphan*/  SPI_CLK_MODE3 ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_LSB_FIRST ; 
#define  SPI_MODE_0 131 
#define  SPI_MODE_1 130 
#define  SPI_MODE_2 129 
#define  SPI_MODE_3 128 
 int /*<<< orphan*/  SPI_PPC4XX_MODE_RD ; 
 int /*<<< orphan*/  SPI_PPC4XX_MODE_SPE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct spi_ppc4xx_cs* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spi_ppc4xx_setup(struct spi_device *spi)
{
	struct spi_ppc4xx_cs *cs = spi->controller_state;

	if (!spi->max_speed_hz) {
		dev_err(&spi->dev, "invalid max_speed_hz (must be non-zero)\n");
		return -EINVAL;
	}

	if (cs == NULL) {
		cs = kzalloc(sizeof *cs, GFP_KERNEL);
		if (!cs)
			return -ENOMEM;
		spi->controller_state = cs;
	}

	/*
	 * We set all bits of the SPI0_MODE register, so,
	 * no need to read-modify-write
	 */
	cs->mode = SPI_PPC4XX_MODE_SPE;

	switch (spi->mode & (SPI_CPHA | SPI_CPOL)) {
	case SPI_MODE_0:
		cs->mode |= SPI_CLK_MODE0;
		break;
	case SPI_MODE_1:
		cs->mode |= SPI_CLK_MODE1;
		break;
	case SPI_MODE_2:
		cs->mode |= SPI_CLK_MODE2;
		break;
	case SPI_MODE_3:
		cs->mode |= SPI_CLK_MODE3;
		break;
	}

	if (spi->mode & SPI_LSB_FIRST)
		cs->mode |= SPI_PPC4XX_MODE_RD;

	return 0;
}