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
struct pcmcia_socket {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int socket_complete_resume(struct pcmcia_socket *skt)
{
	int ret = 0;
#ifdef CONFIG_CARDBUS
	if (skt->state & SOCKET_CARDBUS) {
		/* We can't be sure the CardBus card is the same
		 * as the one previously inserted. Therefore, remove
		 * and re-add... */
		cb_free(skt);
		ret = cb_alloc(skt);
		if (ret)
			cb_free(skt);
	}
#endif
	return ret;
}