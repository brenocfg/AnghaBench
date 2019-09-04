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
typedef  int /*<<< orphan*/  u32 ;
struct spi_message {struct spi_device* spi; } ;
struct spi_master {int dummy; } ;
struct spi_device {int mode; int chip_select; } ;
struct meson_spicc_device {scalar_t__ base; struct spi_message* message; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPICC_BITLENGTH_MASK ; 
 scalar_t__ SPICC_CONREG ; 
 int /*<<< orphan*/  SPICC_CS_MASK ; 
 int SPICC_DRCTL_IGNORE ; 
 int SPICC_DRCTL_LOWLEVEL ; 
 int /*<<< orphan*/  SPICC_DRCTL_MASK ; 
 int /*<<< orphan*/  SPICC_ENABLE ; 
 int /*<<< orphan*/  SPICC_MODE_MASTER ; 
 scalar_t__ SPICC_PERIODREG ; 
 int /*<<< orphan*/  SPICC_PHA ; 
 int /*<<< orphan*/  SPICC_POL ; 
 int /*<<< orphan*/  SPICC_SSPOL ; 
 scalar_t__ SPICC_TESTREG ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int SPI_READY ; 
 struct meson_spicc_device* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writel_bits_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int meson_spicc_prepare_message(struct spi_master *master,
				       struct spi_message *message)
{
	struct meson_spicc_device *spicc = spi_master_get_devdata(master);
	struct spi_device *spi = message->spi;
	u32 conf = 0;

	/* Store current message */
	spicc->message = message;

	/* Enable Master */
	conf |= SPICC_ENABLE;
	conf |= SPICC_MODE_MASTER;

	/* SMC = 0 */

	/* Setup transfer mode */
	if (spi->mode & SPI_CPOL)
		conf |= SPICC_POL;
	else
		conf &= ~SPICC_POL;

	if (spi->mode & SPI_CPHA)
		conf |= SPICC_PHA;
	else
		conf &= ~SPICC_PHA;

	/* SSCTL = 0 */

	if (spi->mode & SPI_CS_HIGH)
		conf |= SPICC_SSPOL;
	else
		conf &= ~SPICC_SSPOL;

	if (spi->mode & SPI_READY)
		conf |= FIELD_PREP(SPICC_DRCTL_MASK, SPICC_DRCTL_LOWLEVEL);
	else
		conf |= FIELD_PREP(SPICC_DRCTL_MASK, SPICC_DRCTL_IGNORE);

	/* Select CS */
	conf |= FIELD_PREP(SPICC_CS_MASK, spi->chip_select);

	/* Default Clock rate core/4 */

	/* Default 8bit word */
	conf |= FIELD_PREP(SPICC_BITLENGTH_MASK, 8 - 1);

	writel_relaxed(conf, spicc->base + SPICC_CONREG);

	/* Setup no wait cycles by default */
	writel_relaxed(0, spicc->base + SPICC_PERIODREG);

	writel_bits_relaxed(BIT(24), BIT(24), spicc->base + SPICC_TESTREG);

	return 0;
}