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
struct spi_device {int chip_select; int /*<<< orphan*/  master; struct omap1_spi100k_cs* controller_state; int /*<<< orphan*/  dev; } ;
struct omap1_spi100k_cs {scalar_t__ base; } ;
struct omap1_spi100k {int /*<<< orphan*/  fck; int /*<<< orphan*/  ick; scalar_t__ base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct omap1_spi100k_cs* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int omap1_spi100k_setup_transfer (struct spi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi100k_open (int /*<<< orphan*/ ) ; 
 struct omap1_spi100k* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap1_spi100k_setup(struct spi_device *spi)
{
	int                     ret;
	struct omap1_spi100k    *spi100k;
	struct omap1_spi100k_cs *cs = spi->controller_state;

	spi100k = spi_master_get_devdata(spi->master);

	if (!cs) {
		cs = devm_kzalloc(&spi->dev, sizeof(*cs), GFP_KERNEL);
		if (!cs)
			return -ENOMEM;
		cs->base = spi100k->base + spi->chip_select * 0x14;
		spi->controller_state = cs;
	}

	spi100k_open(spi->master);

	clk_prepare_enable(spi100k->ick);
	clk_prepare_enable(spi100k->fck);

	ret = omap1_spi100k_setup_transfer(spi, NULL);

	clk_disable_unprepare(spi100k->ick);
	clk_disable_unprepare(spi100k->fck);

	return ret;
}