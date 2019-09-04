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
struct spi_master {int dummy; } ;
struct omap2_mcspi_regs {int modulctrl; } ;
struct omap2_mcspi {struct omap2_mcspi_regs ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP2_MCSPI_MODULCTRL ; 
 int OMAP2_MCSPI_MODULCTRL_MS ; 
 int OMAP2_MCSPI_MODULCTRL_SINGLE ; 
 int OMAP2_MCSPI_MODULCTRL_STEST ; 
 int mcspi_read_reg (struct spi_master*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcspi_write_reg (struct spi_master*,int /*<<< orphan*/ ,int) ; 
 struct omap2_mcspi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static void omap2_mcspi_set_master_mode(struct spi_master *master)
{
	struct omap2_mcspi	*mcspi = spi_master_get_devdata(master);
	struct omap2_mcspi_regs	*ctx = &mcspi->ctx;
	u32 l;

	/*
	 * Setup when switching from (reset default) slave mode
	 * to single-channel master mode
	 */
	l = mcspi_read_reg(master, OMAP2_MCSPI_MODULCTRL);
	l &= ~(OMAP2_MCSPI_MODULCTRL_STEST | OMAP2_MCSPI_MODULCTRL_MS);
	l |= OMAP2_MCSPI_MODULCTRL_SINGLE;
	mcspi_write_reg(master, OMAP2_MCSPI_MODULCTRL, l);

	ctx->modulctrl = l;
}