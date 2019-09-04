#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dsr; int /*<<< orphan*/  rng; } ;
struct TYPE_5__ {TYPE_1__ icount; } ;
struct tegra_uart_port {TYPE_2__ uport; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_MSR ; 
 unsigned long UART_MSR_ANY_DELTA ; 
 unsigned long UART_MSR_CTS ; 
 unsigned long UART_MSR_DCD ; 
 unsigned long UART_MSR_DCTS ; 
 unsigned long UART_MSR_DDCD ; 
 unsigned long UART_MSR_DDSR ; 
 unsigned long UART_MSR_TERI ; 
 unsigned long tegra_uart_read (struct tegra_uart_port*,int /*<<< orphan*/ ) ; 
 struct tegra_uart_port* to_tegra_uport (struct uart_port*) ; 
 int /*<<< orphan*/  uart_handle_cts_change (TYPE_2__*,unsigned long) ; 
 int /*<<< orphan*/  uart_handle_dcd_change (TYPE_2__*,unsigned long) ; 

__attribute__((used)) static void tegra_uart_handle_modem_signal_change(struct uart_port *u)
{
	struct tegra_uart_port *tup = to_tegra_uport(u);
	unsigned long msr;

	msr = tegra_uart_read(tup, UART_MSR);
	if (!(msr & UART_MSR_ANY_DELTA))
		return;

	if (msr & UART_MSR_TERI)
		tup->uport.icount.rng++;
	if (msr & UART_MSR_DDSR)
		tup->uport.icount.dsr++;
	/* We may only get DDCD when HW init and reset */
	if (msr & UART_MSR_DDCD)
		uart_handle_dcd_change(&tup->uport, msr & UART_MSR_DCD);
	/* Will start/stop_tx accordingly */
	if (msr & UART_MSR_DCTS)
		uart_handle_cts_change(&tup->uport, msr & UART_MSR_CTS);
}