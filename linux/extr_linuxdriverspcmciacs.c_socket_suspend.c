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
struct pcmcia_socket {int state; int suspended_state; int /*<<< orphan*/  ops_mutex; TYPE_1__* ops; int /*<<< orphan*/  socket; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* suspend ) (struct pcmcia_socket*) ;int /*<<< orphan*/  (* set_socket ) (struct pcmcia_socket*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int SOCKET_IN_RESUME ; 
 int SOCKET_SUSPEND ; 
 int /*<<< orphan*/  dead_socket ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct pcmcia_socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct pcmcia_socket*) ; 

__attribute__((used)) static int socket_suspend(struct pcmcia_socket *skt)
{
	if ((skt->state & SOCKET_SUSPEND) && !(skt->state & SOCKET_IN_RESUME))
		return -EBUSY;

	mutex_lock(&skt->ops_mutex);
	/* store state on first suspend, but not after spurious wakeups */
	if (!(skt->state & SOCKET_IN_RESUME))
		skt->suspended_state = skt->state;

	skt->socket = dead_socket;
	skt->ops->set_socket(skt, &skt->socket);
	if (skt->ops->suspend)
		skt->ops->suspend(skt);
	skt->state |= SOCKET_SUSPEND;
	skt->state &= ~SOCKET_IN_RESUME;
	mutex_unlock(&skt->ops_mutex);
	return 0;
}