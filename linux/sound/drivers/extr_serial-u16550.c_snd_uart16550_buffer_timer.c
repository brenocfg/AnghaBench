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
struct timer_list {int dummy; } ;
struct snd_uart16550 {int /*<<< orphan*/  open_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_timer ; 
 struct snd_uart16550* from_timer (struct snd_uart16550*,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_uart16550_del_timer (struct snd_uart16550*) ; 
 int /*<<< orphan*/  snd_uart16550_io_loop (struct snd_uart16550*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_uart16550_buffer_timer(struct timer_list *t)
{
	unsigned long flags;
	struct snd_uart16550 *uart;

	uart = from_timer(uart, t, buffer_timer);
	spin_lock_irqsave(&uart->open_lock, flags);
	snd_uart16550_del_timer(uart);
	snd_uart16550_io_loop(uart);
	spin_unlock_irqrestore(&uart->open_lock, flags);
}