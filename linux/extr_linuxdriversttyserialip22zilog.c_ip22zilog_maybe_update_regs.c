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
struct zilog_channel {int dummy; } ;
struct uart_ip22zilog_port {int /*<<< orphan*/  curregs; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP22ZILOG_FLAG_REGS_HELD ; 
 int /*<<< orphan*/  ZS_REGS_HELD (struct uart_ip22zilog_port*) ; 
 scalar_t__ ZS_TX_ACTIVE (struct uart_ip22zilog_port*) ; 
 int /*<<< orphan*/  __load_zsregs (struct zilog_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ip22zilog_maybe_update_regs(struct uart_ip22zilog_port *up,
				       struct zilog_channel *channel)
{
	if (!ZS_REGS_HELD(up)) {
		if (ZS_TX_ACTIVE(up)) {
			up->flags |= IP22ZILOG_FLAG_REGS_HELD;
		} else {
			__load_zsregs(channel, up->curregs);
		}
	}
}