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
struct db1x_pcmcia_sock {int stschg_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int) ; 
 int /*<<< orphan*/  enable_irq (int) ; 

__attribute__((used)) static inline void set_stschg(struct db1x_pcmcia_sock *sock, int en)
{
	if (sock->stschg_irq != -1) {
		if (en)
			enable_irq(sock->stschg_irq);
		else
			disable_irq(sock->stschg_irq);
	}
}