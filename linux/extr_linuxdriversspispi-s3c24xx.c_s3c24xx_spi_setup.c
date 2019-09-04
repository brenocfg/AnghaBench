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
struct spi_device {struct s3c24xx_spi_devstate* controller_state; int /*<<< orphan*/  dev; } ;
struct s3c24xx_spi_devstate {int hz; int /*<<< orphan*/  spcon; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  (* chipselect ) (struct spi_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  busy; } ;
struct s3c24xx_spi {TYPE_1__ bitbang; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITBANG_CS_INACTIVE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SPCON_DEFAULT ; 
 struct s3c24xx_spi_devstate* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int s3c24xx_spi_update_state (struct spi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct spi_device*,int /*<<< orphan*/ ) ; 
 struct s3c24xx_spi* to_hw (struct spi_device*) ; 

__attribute__((used)) static int s3c24xx_spi_setup(struct spi_device *spi)
{
	struct s3c24xx_spi_devstate *cs = spi->controller_state;
	struct s3c24xx_spi *hw = to_hw(spi);
	int ret;

	/* allocate settings on the first call */
	if (!cs) {
		cs = devm_kzalloc(&spi->dev,
				  sizeof(struct s3c24xx_spi_devstate),
				  GFP_KERNEL);
		if (!cs)
			return -ENOMEM;

		cs->spcon = SPCON_DEFAULT;
		cs->hz = -1;
		spi->controller_state = cs;
	}

	/* initialise the state from the device */
	ret = s3c24xx_spi_update_state(spi, NULL);
	if (ret)
		return ret;

	mutex_lock(&hw->bitbang.lock);
	if (!hw->bitbang.busy) {
		hw->bitbang.chipselect(spi, BITBANG_CS_INACTIVE);
		/* need to ndelay for 0.5 clocktick ? */
	}
	mutex_unlock(&hw->bitbang.lock);

	return 0;
}