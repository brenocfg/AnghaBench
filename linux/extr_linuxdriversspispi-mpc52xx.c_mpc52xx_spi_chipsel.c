#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mpc52xx_spi {scalar_t__ gpio_cs_count; scalar_t__ regs; int /*<<< orphan*/ * gpio_cs; TYPE_2__* message; } ;
struct TYPE_4__ {TYPE_1__* spi; } ;
struct TYPE_3__ {int chip_select; } ;

/* Variables and functions */
 scalar_t__ SPI_PORTDATA ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_8 (scalar_t__,int) ; 

__attribute__((used)) static void mpc52xx_spi_chipsel(struct mpc52xx_spi *ms, int value)
{
	int cs;

	if (ms->gpio_cs_count > 0) {
		cs = ms->message->spi->chip_select;
		gpio_set_value(ms->gpio_cs[cs], value ? 0 : 1);
	} else
		out_8(ms->regs + SPI_PORTDATA, value ? 0 : 0x08);
}