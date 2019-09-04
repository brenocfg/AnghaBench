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
struct zilog_channel {int /*<<< orphan*/  control; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 struct zilog_channel* ZILOG_CHANNEL_FROM_PORT (struct uart_port*) ; 
 int /*<<< orphan*/  ZSDELAY () ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline__ unsigned char ip22zilog_read_channel_status(struct uart_port *port)
{
	struct zilog_channel *channel;
	unsigned char status;

	channel = ZILOG_CHANNEL_FROM_PORT(port);
	status = readb(&channel->control);
	ZSDELAY();

	return status;
}