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
struct spi_device {int bits_per_word; int /*<<< orphan*/  max_speed_hz; struct mpc52xx_psc_spi_cs* controller_state; int /*<<< orphan*/  master; } ;
struct mpc52xx_psc_spi_cs {int bits_per_word; int /*<<< orphan*/  speed_hz; } ;
struct mpc52xx_psc_spi {int /*<<< orphan*/  lock; int /*<<< orphan*/  busy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mpc52xx_psc_spi_cs* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc52xx_psc_spi_deactivate_cs (struct spi_device*) ; 
 struct mpc52xx_psc_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mpc52xx_psc_spi_setup(struct spi_device *spi)
{
	struct mpc52xx_psc_spi *mps = spi_master_get_devdata(spi->master);
	struct mpc52xx_psc_spi_cs *cs = spi->controller_state;
	unsigned long flags;

	if (spi->bits_per_word%8)
		return -EINVAL;

	if (!cs) {
		cs = kzalloc(sizeof *cs, GFP_KERNEL);
		if (!cs)
			return -ENOMEM;
		spi->controller_state = cs;
	}

	cs->bits_per_word = spi->bits_per_word;
	cs->speed_hz = spi->max_speed_hz;

	spin_lock_irqsave(&mps->lock, flags);
	if (!mps->busy)
		mpc52xx_psc_spi_deactivate_cs(spi);
	spin_unlock_irqrestore(&mps->lock, flags);

	return 0;
}