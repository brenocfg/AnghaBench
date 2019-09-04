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
struct jcore_spi {int speed_hz; int clock_freq; int speed_reg; TYPE_2__* master; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  jcore_spi_program (struct jcore_spi*) ; 

__attribute__((used)) static void jcore_spi_baudrate(struct jcore_spi *hw, int speed)
{
	if (speed == hw->speed_hz) return;
	hw->speed_hz = speed;
	if (speed >= hw->clock_freq / 2)
		hw->speed_reg = 0;
	else
		hw->speed_reg = ((hw->clock_freq / 2 / speed) - 1) << 27;
	jcore_spi_program(hw);
	dev_dbg(hw->master->dev.parent, "speed=%d reg=0x%x\n",
		speed, hw->speed_reg);
}