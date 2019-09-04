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
struct db1x_pcmcia_sock {int stschg_irq; int insert_irq; int eject_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int,struct db1x_pcmcia_sock*) ; 

__attribute__((used)) static void db1x_pcmcia_free_irqs(struct db1x_pcmcia_sock *sock)
{
	if (sock->stschg_irq != -1)
		free_irq(sock->stschg_irq, sock);

	free_irq(sock->insert_irq, sock);
	if (sock->eject_irq != -1)
		free_irq(sock->eject_irq, sock);
}