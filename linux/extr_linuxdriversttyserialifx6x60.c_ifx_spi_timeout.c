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
struct timer_list {int dummy; } ;
struct ifx_spi_device {int /*<<< orphan*/  flags; int /*<<< orphan*/  tty_port; TYPE_1__* spi_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFX_SPI_STATE_TIMER_PENDING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct ifx_spi_device* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct ifx_spi_device* ifx_dev ; 
 int /*<<< orphan*/  mrdy_set_low (struct ifx_spi_device*) ; 
 int /*<<< orphan*/  spi_timer ; 
 int /*<<< orphan*/  tty_port_tty_hangup (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ifx_spi_timeout(struct timer_list *t)
{
	struct ifx_spi_device *ifx_dev = from_timer(ifx_dev, t, spi_timer);

	dev_warn(&ifx_dev->spi_dev->dev, "*** SPI Timeout ***");
	tty_port_tty_hangup(&ifx_dev->tty_port, false);
	mrdy_set_low(ifx_dev);
	clear_bit(IFX_SPI_STATE_TIMER_PENDING, &ifx_dev->flags);
}