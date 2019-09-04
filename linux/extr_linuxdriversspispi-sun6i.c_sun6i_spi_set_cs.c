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
struct sun6i_spi {int dummy; } ;
struct spi_device {int /*<<< orphan*/  chip_select; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUN6I_TFR_CTL_CS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN6I_TFR_CTL_CS_LEVEL ; 
 int /*<<< orphan*/  SUN6I_TFR_CTL_CS_MASK ; 
 int /*<<< orphan*/  SUN6I_TFR_CTL_REG ; 
 struct sun6i_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun6i_spi_read (struct sun6i_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun6i_spi_write (struct sun6i_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun6i_spi_set_cs(struct spi_device *spi, bool enable)
{
	struct sun6i_spi *sspi = spi_master_get_devdata(spi->master);
	u32 reg;

	reg = sun6i_spi_read(sspi, SUN6I_TFR_CTL_REG);
	reg &= ~SUN6I_TFR_CTL_CS_MASK;
	reg |= SUN6I_TFR_CTL_CS(spi->chip_select);

	if (enable)
		reg |= SUN6I_TFR_CTL_CS_LEVEL;
	else
		reg &= ~SUN6I_TFR_CTL_CS_LEVEL;

	sun6i_spi_write(sspi, SUN6I_TFR_CTL_REG, reg);
}