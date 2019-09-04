#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_6__ {int rx; } ;
struct uart_port {TYPE_3__ icount; scalar_t__ membase; TYPE_1__* state; } ;
struct tty_port {int dummy; } ;
struct men_z135_port {TYPE_2__* mdev; int /*<<< orphan*/  rxbuf; struct uart_port port; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct tty_port port; } ;

/* Variables and functions */
 int MEN_Z135_FIFO_WATERMARK ; 
 scalar_t__ MEN_Z135_RX_CTRL ; 
 scalar_t__ MEN_Z135_RX_RAM ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,...) ; 
 int get_rx_fifo_content (struct men_z135_port*) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int tty_buffer_request_room (struct tty_port*,int) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int tty_insert_flip_string (struct tty_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void men_z135_handle_rx(struct men_z135_port *uart)
{
	struct uart_port *port = &uart->port;
	struct tty_port *tport = &port->state->port;
	int copied;
	u16 size;
	int room;

	size = get_rx_fifo_content(uart);

	if (size == 0)
		return;

	/* Avoid accidently accessing TX FIFO instead of RX FIFO. Last
	 * longword in RX FIFO cannot be read.(0x004-0x3FF)
	 */
	if (size > MEN_Z135_FIFO_WATERMARK)
		size = MEN_Z135_FIFO_WATERMARK;

	room = tty_buffer_request_room(tport, size);
	if (room != size)
		dev_warn(&uart->mdev->dev,
			"Not enough room in flip buffer, truncating to %d\n",
			room);

	if (room == 0)
		return;

	memcpy_fromio(uart->rxbuf, port->membase + MEN_Z135_RX_RAM, room);
	/* Be sure to first copy all data and then acknowledge it */
	mb();
	iowrite32(room, port->membase +  MEN_Z135_RX_CTRL);

	copied = tty_insert_flip_string(tport, uart->rxbuf, room);
	if (copied != room)
		dev_warn(&uart->mdev->dev,
			"Only copied %d instead of %d bytes\n",
			copied, room);

	port->icount.rx += copied;

	tty_flip_buffer_push(tport);

}