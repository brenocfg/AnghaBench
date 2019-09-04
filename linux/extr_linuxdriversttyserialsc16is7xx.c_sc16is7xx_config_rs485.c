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
struct serial_rs485 {int flags; scalar_t__ delay_rts_after_send; } ;
struct uart_port {struct serial_rs485 rs485; int /*<<< orphan*/  dev; } ;
struct sc16is7xx_port {int /*<<< orphan*/  kworker; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct sc16is7xx_one {int /*<<< orphan*/  reg_work; TYPE_1__ config; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SC16IS7XX_RECONF_RS485 ; 
 int SER_RS485_ENABLED ; 
 int SER_RS485_RTS_AFTER_SEND ; 
 int SER_RS485_RTS_ON_SEND ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 struct sc16is7xx_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sc16is7xx_one* to_sc16is7xx_one (struct uart_port*,struct uart_port*) ; 

__attribute__((used)) static int sc16is7xx_config_rs485(struct uart_port *port,
				  struct serial_rs485 *rs485)
{
	struct sc16is7xx_port *s = dev_get_drvdata(port->dev);
	struct sc16is7xx_one *one = to_sc16is7xx_one(port, port);

	if (rs485->flags & SER_RS485_ENABLED) {
		bool rts_during_rx, rts_during_tx;

		rts_during_rx = rs485->flags & SER_RS485_RTS_AFTER_SEND;
		rts_during_tx = rs485->flags & SER_RS485_RTS_ON_SEND;

		if (rts_during_rx == rts_during_tx)
			dev_err(port->dev,
				"unsupported RTS signalling on_send:%d after_send:%d - exactly one of RS485 RTS flags should be set\n",
				rts_during_tx, rts_during_rx);

		/*
		 * RTS signal is handled by HW, it's timing can't be influenced.
		 * However, it's sometimes useful to delay TX even without RTS
		 * control therefore we try to handle .delay_rts_before_send.
		 */
		if (rs485->delay_rts_after_send)
			return -EINVAL;
	}

	port->rs485 = *rs485;
	one->config.flags |= SC16IS7XX_RECONF_RS485;
	kthread_queue_work(&s->kworker, &one->reg_work);

	return 0;
}