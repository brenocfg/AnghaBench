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
struct pcmcia_socket {int state; int suspended_state; TYPE_1__* callback; int /*<<< orphan*/  dev; scalar_t__ resume_status; int /*<<< orphan*/  ops_mutex; } ;
struct TYPE_2__ {int (* early_resume ) (struct pcmcia_socket*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int SOCKET_CARDBUS ; 
 int SOCKET_IN_RESUME ; 
 int SOCKET_PRESENT ; 
 int SOCKET_SUSPEND ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int socket_insert (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  socket_shutdown (struct pcmcia_socket*) ; 
 int stub1 (struct pcmcia_socket*) ; 

__attribute__((used)) static int socket_late_resume(struct pcmcia_socket *skt)
{
	int ret = 0;

	mutex_lock(&skt->ops_mutex);
	skt->state &= ~(SOCKET_SUSPEND | SOCKET_IN_RESUME);
	mutex_unlock(&skt->ops_mutex);

	if (!(skt->state & SOCKET_PRESENT)) {
		ret = socket_insert(skt);
		if (ret == -ENODEV)
			ret = 0;
		return ret;
	}

	if (skt->resume_status) {
		socket_shutdown(skt);
		return 0;
	}

	if (skt->suspended_state != skt->state) {
		dev_dbg(&skt->dev,
			"suspend state 0x%x != resume state 0x%x\n",
			skt->suspended_state, skt->state);

		socket_shutdown(skt);
		return socket_insert(skt);
	}

	if (!(skt->state & SOCKET_CARDBUS) && (skt->callback))
		ret = skt->callback->early_resume(skt);
	return ret;
}