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
struct tty_struct {struct mxser_port* driver_data; } ;
struct mxser_port {int /*<<< orphan*/  slock; scalar_t__ ioaddr; scalar_t__ xmit_tail; scalar_t__ xmit_head; scalar_t__ xmit_cnt; } ;

/* Variables and functions */
 scalar_t__ UART_FCR ; 
 char UART_FCR_CLEAR_RCVR ; 
 char UART_FCR_CLEAR_XMIT ; 
 char inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (char,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 

__attribute__((used)) static void mxser_flush_buffer(struct tty_struct *tty)
{
	struct mxser_port *info = tty->driver_data;
	char fcr;
	unsigned long flags;


	spin_lock_irqsave(&info->slock, flags);
	info->xmit_cnt = info->xmit_head = info->xmit_tail = 0;

	fcr = inb(info->ioaddr + UART_FCR);
	outb((fcr | UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT),
		info->ioaddr + UART_FCR);
	outb(fcr, info->ioaddr + UART_FCR);

	spin_unlock_irqrestore(&info->slock, flags);

	tty_wakeup(tty);
}