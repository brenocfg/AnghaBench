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
struct zilog_channel {int dummy; } ;
struct uart_ip22zilog_port {int flags; TYPE_1__* next; int /*<<< orphan*/  port; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 unsigned char ALL_SNT ; 
 int /*<<< orphan*/  FHWRES ; 
 int IP22ZILOG_FLAG_RESET_DONE ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R1 ; 
 int /*<<< orphan*/  R9 ; 
 struct zilog_channel* ZILOG_CHANNEL_FROM_PORT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSDELAY_LONG () ; 
 int /*<<< orphan*/  ZS_IS_CHANNEL_A (struct uart_ip22zilog_port*) ; 
 unsigned char read_zsreg (struct zilog_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_zsreg (struct zilog_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __ip22zilog_reset(struct uart_ip22zilog_port *up)
{
	struct zilog_channel *channel;
	int i;

	if (up->flags & IP22ZILOG_FLAG_RESET_DONE)
		return;

	/* Let pending transmits finish.  */
	channel = ZILOG_CHANNEL_FROM_PORT(&up->port);
	for (i = 0; i < 1000; i++) {
		unsigned char stat = read_zsreg(channel, R1);
		if (stat & ALL_SNT)
			break;
		udelay(100);
	}

	if (!ZS_IS_CHANNEL_A(up)) {
		up++;
		channel = ZILOG_CHANNEL_FROM_PORT(&up->port);
	}
	write_zsreg(channel, R9, FHWRES);
	ZSDELAY_LONG();
	(void) read_zsreg(channel, R0);

	up->flags |= IP22ZILOG_FLAG_RESET_DONE;
	up->next->flags |= IP22ZILOG_FLAG_RESET_DONE;
}