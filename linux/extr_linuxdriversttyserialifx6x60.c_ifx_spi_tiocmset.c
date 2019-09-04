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
struct tty_struct {struct ifx_spi_device* driver_data; } ;
struct ifx_spi_device {int /*<<< orphan*/  signal_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFX_SPI_DTR ; 
 int /*<<< orphan*/  IFX_SPI_RTS ; 
 int /*<<< orphan*/  IFX_SPI_UPDATE ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ifx_spi_tiocmset(struct tty_struct *tty,
			    unsigned int set, unsigned int clear)
{
	struct ifx_spi_device *ifx_dev = tty->driver_data;

	if (set & TIOCM_RTS)
		set_bit(IFX_SPI_RTS, &ifx_dev->signal_state);
	if (set & TIOCM_DTR)
		set_bit(IFX_SPI_DTR, &ifx_dev->signal_state);
	if (clear & TIOCM_RTS)
		clear_bit(IFX_SPI_RTS, &ifx_dev->signal_state);
	if (clear & TIOCM_DTR)
		clear_bit(IFX_SPI_DTR, &ifx_dev->signal_state);

	set_bit(IFX_SPI_UPDATE, &ifx_dev->signal_state);
	return 0;
}