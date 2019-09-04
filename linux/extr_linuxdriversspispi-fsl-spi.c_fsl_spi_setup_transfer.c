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
typedef  int u8 ;
typedef  int u32 ;
struct spi_transfer {int bits_per_word; int speed_hz; } ;
struct spi_mpc8xxx_cs {int hw_mode; } ;
struct spi_device {int bits_per_word; int max_speed_hz; int /*<<< orphan*/  dev; int /*<<< orphan*/  master; struct spi_mpc8xxx_cs* controller_state; } ;
struct mpc8xxx_spi {int flags; int spibrg; } ;

/* Variables and functions */
 int SPI_CPM_MODE ; 
 int SPI_QE ; 
 int SPMODE_DIV16 ; 
 int SPMODE_LEN (int) ; 
 int SPMODE_PM (int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_spi_change_mode (struct spi_device*) ; 
 int mspi_apply_cpu_mode_quirks (struct spi_mpc8xxx_cs*,struct spi_device*,struct mpc8xxx_spi*,int) ; 
 int mspi_apply_qe_mode_quirks (struct spi_mpc8xxx_cs*,struct spi_device*,int) ; 
 struct mpc8xxx_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsl_spi_setup_transfer(struct spi_device *spi,
					struct spi_transfer *t)
{
	struct mpc8xxx_spi *mpc8xxx_spi;
	int bits_per_word = 0;
	u8 pm;
	u32 hz = 0;
	struct spi_mpc8xxx_cs	*cs = spi->controller_state;

	mpc8xxx_spi = spi_master_get_devdata(spi->master);

	if (t) {
		bits_per_word = t->bits_per_word;
		hz = t->speed_hz;
	}

	/* spi_transfer level calls that work per-word */
	if (!bits_per_word)
		bits_per_word = spi->bits_per_word;

	if (!hz)
		hz = spi->max_speed_hz;

	if (!(mpc8xxx_spi->flags & SPI_CPM_MODE))
		bits_per_word = mspi_apply_cpu_mode_quirks(cs, spi,
							   mpc8xxx_spi,
							   bits_per_word);
	else if (mpc8xxx_spi->flags & SPI_QE)
		bits_per_word = mspi_apply_qe_mode_quirks(cs, spi,
							  bits_per_word);

	if (bits_per_word < 0)
		return bits_per_word;

	if (bits_per_word == 32)
		bits_per_word = 0;
	else
		bits_per_word = bits_per_word - 1;

	/* mask out bits we are going to set */
	cs->hw_mode &= ~(SPMODE_LEN(0xF) | SPMODE_DIV16
				  | SPMODE_PM(0xF));

	cs->hw_mode |= SPMODE_LEN(bits_per_word);

	if ((mpc8xxx_spi->spibrg / hz) > 64) {
		cs->hw_mode |= SPMODE_DIV16;
		pm = (mpc8xxx_spi->spibrg - 1) / (hz * 64) + 1;
		WARN_ONCE(pm > 16,
			  "%s: Requested speed is too low: %d Hz. Will use %d Hz instead.\n",
			  dev_name(&spi->dev), hz, mpc8xxx_spi->spibrg / 1024);
		if (pm > 16)
			pm = 16;
	} else {
		pm = (mpc8xxx_spi->spibrg - 1) / (hz * 4) + 1;
	}
	if (pm)
		pm--;

	cs->hw_mode |= SPMODE_PM(pm);

	fsl_spi_change_mode(spi);
	return 0;
}