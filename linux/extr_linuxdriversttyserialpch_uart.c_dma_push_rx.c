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
struct TYPE_3__ {int rx; } ;
struct uart_port {TYPE_1__ icount; int /*<<< orphan*/  dev; TYPE_2__* state; } ;
struct tty_port {int dummy; } ;
struct eg20t_port {int /*<<< orphan*/  sg_rx; struct uart_port port; } ;
struct TYPE_4__ {struct tty_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sg_virt (int /*<<< orphan*/ *) ; 
 int tty_buffer_request_room (struct tty_port*,int) ; 
 int /*<<< orphan*/  tty_insert_flip_string (struct tty_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dma_push_rx(struct eg20t_port *priv, int size)
{
	int room;
	struct uart_port *port = &priv->port;
	struct tty_port *tport = &port->state->port;

	room = tty_buffer_request_room(tport, size);

	if (room < size)
		dev_warn(port->dev, "Rx overrun: dropping %u bytes\n",
			 size - room);
	if (!room)
		return 0;

	tty_insert_flip_string(tport, sg_virt(&priv->sg_rx), size);

	port->icount.rx += room;

	return room;
}