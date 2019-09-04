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
struct spi_device {struct omap2_mcspi_cs* controller_state; } ;
struct omap2_mcspi_cs {int /*<<< orphan*/  chctrl0; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP2_MCSPI_CHCTRL0 ; 
 int /*<<< orphan*/  OMAP2_MCSPI_CHCTRL_EN ; 
 int /*<<< orphan*/  mcspi_read_cs_reg (struct spi_device const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcspi_write_cs_reg (struct spi_device const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap2_mcspi_set_enable(const struct spi_device *spi, int enable)
{
	struct omap2_mcspi_cs *cs = spi->controller_state;
	u32 l;

	l = cs->chctrl0;
	if (enable)
		l |= OMAP2_MCSPI_CHCTRL_EN;
	else
		l &= ~OMAP2_MCSPI_CHCTRL_EN;
	cs->chctrl0 = l;
	mcspi_write_cs_reg(spi, OMAP2_MCSPI_CHCTRL0, cs->chctrl0);
	/* Flash post-writes */
	mcspi_read_cs_reg(spi, OMAP2_MCSPI_CHCTRL0);
}