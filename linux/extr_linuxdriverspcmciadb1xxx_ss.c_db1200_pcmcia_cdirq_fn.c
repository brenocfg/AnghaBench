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
struct db1x_pcmcia_sock {int insert_irq; int eject_irq; int /*<<< orphan*/  socket; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SS_DETECT ; 
 int /*<<< orphan*/  enable_irq (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pcmcia_parse_events (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t db1200_pcmcia_cdirq_fn(int irq, void *data)
{
	struct db1x_pcmcia_sock *sock = data;

	/* Wait a bit for the signals to stop bouncing. */
	msleep(100);
	if (irq == sock->insert_irq)
		enable_irq(sock->eject_irq);
	else
		enable_irq(sock->insert_irq);

	pcmcia_parse_events(&sock->socket, SS_DETECT);

	return IRQ_HANDLED;
}