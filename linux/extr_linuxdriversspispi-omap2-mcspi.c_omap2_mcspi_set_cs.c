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
struct spi_device {int mode; scalar_t__ controller_state; int /*<<< orphan*/  master; } ;
struct omap2_mcspi {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP2_MCSPI_CHCONF_FORCE ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mcspi_cached_chconf0 (struct spi_device*) ; 
 int /*<<< orphan*/  mcspi_write_chconf0 (struct spi_device*,int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 struct omap2_mcspi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap2_mcspi_set_cs(struct spi_device *spi, bool enable)
{
	struct omap2_mcspi *mcspi = spi_master_get_devdata(spi->master);
	u32 l;

	/* The controller handles the inverted chip selects
	 * using the OMAP2_MCSPI_CHCONF_EPOL bit so revert
	 * the inversion from the core spi_set_cs function.
	 */
	if (spi->mode & SPI_CS_HIGH)
		enable = !enable;

	if (spi->controller_state) {
		int err = pm_runtime_get_sync(mcspi->dev);
		if (err < 0) {
			pm_runtime_put_noidle(mcspi->dev);
			dev_err(mcspi->dev, "failed to get sync: %d\n", err);
			return;
		}

		l = mcspi_cached_chconf0(spi);

		if (enable)
			l &= ~OMAP2_MCSPI_CHCONF_FORCE;
		else
			l |= OMAP2_MCSPI_CHCONF_FORCE;

		mcspi_write_chconf0(spi, l);

		pm_runtime_mark_last_busy(mcspi->dev);
		pm_runtime_put_autosuspend(mcspi->dev);
	}
}