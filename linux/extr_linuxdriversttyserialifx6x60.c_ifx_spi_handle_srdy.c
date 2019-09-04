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
struct ifx_spi_device {int /*<<< orphan*/  flags; int /*<<< orphan*/  io_work_tasklet; int /*<<< orphan*/  spi_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFX_SPI_POWER_SRDY ; 
 int /*<<< orphan*/  IFX_SPI_STATE_IO_IN_PROGRESS ; 
 int /*<<< orphan*/  IFX_SPI_STATE_IO_READY ; 
 int /*<<< orphan*/  IFX_SPI_STATE_TIMER_PENDING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifx_spi_power_state_set (struct ifx_spi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ifx_spi_handle_srdy(struct ifx_spi_device *ifx_dev)
{
	if (test_bit(IFX_SPI_STATE_TIMER_PENDING, &ifx_dev->flags)) {
		del_timer(&ifx_dev->spi_timer);
		clear_bit(IFX_SPI_STATE_TIMER_PENDING, &ifx_dev->flags);
	}

	ifx_spi_power_state_set(ifx_dev, IFX_SPI_POWER_SRDY);

	if (!test_bit(IFX_SPI_STATE_IO_IN_PROGRESS, &ifx_dev->flags))
		tasklet_schedule(&ifx_dev->io_work_tasklet);
	else
		set_bit(IFX_SPI_STATE_IO_READY, &ifx_dev->flags);
}