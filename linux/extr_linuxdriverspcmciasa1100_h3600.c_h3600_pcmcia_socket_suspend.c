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
struct soc_pcmcia_socket {int nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  H3XXX_EGPIO_OPT_NVRAM_ON ; 
 int /*<<< orphan*/  H3XXX_EGPIO_OPT_ON ; 
 int /*<<< orphan*/  H3XXX_EGPIO_OPT_RESET ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void h3600_pcmcia_socket_suspend(struct soc_pcmcia_socket *skt)
{
	/*
	 * FIXME:  This doesn't fit well.  We don't have the mechanism in
	 * the generic PCMCIA layer to deal with the idea of two sockets
	 * on one bus.  We rely on the cs.c behaviour shutting down
	 * socket 0 then socket 1.
	 */
	if (skt->nr == 1) {
		gpio_set_value(H3XXX_EGPIO_OPT_ON, 0);
		gpio_set_value(H3XXX_EGPIO_OPT_NVRAM_ON, 0);
		/* hmm, does this suck power? */
		gpio_set_value(H3XXX_EGPIO_OPT_RESET, 1);
	}
}