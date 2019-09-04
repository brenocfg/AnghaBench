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
typedef  int u8 ;
struct men_z135_port {int stat_reg; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int MEN_Z135_MSR_CTS ; 
 int MEN_Z135_MSR_DCD ; 
 int MEN_Z135_MSR_DCTS ; 
 int MEN_Z135_MSR_DDCD ; 
 int /*<<< orphan*/  uart_handle_cts_change (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uart_handle_dcd_change (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void men_z135_handle_modem_status(struct men_z135_port *uart)
{
	u8 msr;

	msr = (uart->stat_reg >> 8) & 0xff;

	if (msr & MEN_Z135_MSR_DDCD)
		uart_handle_dcd_change(&uart->port,
				msr & MEN_Z135_MSR_DCD);
	if (msr & MEN_Z135_MSR_DCTS)
		uart_handle_cts_change(&uart->port,
				msr & MEN_Z135_MSR_CTS);
}