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
struct pcmcia_socket {int /*<<< orphan*/  socket_released; int /*<<< orphan*/  ops_mutex; TYPE_1__* resource_ops; int /*<<< orphan*/  socket_list; scalar_t__ thread; int /*<<< orphan*/  ops; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* exit ) (struct pcmcia_socket*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_socket_list_rwsem ; 
 int /*<<< orphan*/  stub1 (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void pcmcia_unregister_socket(struct pcmcia_socket *socket)
{
	if (!socket)
		return;

	dev_dbg(&socket->dev, "pcmcia_unregister_socket(0x%p)\n", socket->ops);

	if (socket->thread)
		kthread_stop(socket->thread);

	/* remove from our own list */
	down_write(&pcmcia_socket_list_rwsem);
	list_del(&socket->socket_list);
	up_write(&pcmcia_socket_list_rwsem);

	/* wait for sysfs to drop all references */
	if (socket->resource_ops->exit) {
		mutex_lock(&socket->ops_mutex);
		socket->resource_ops->exit(socket);
		mutex_unlock(&socket->ops_mutex);
	}
	wait_for_completion(&socket->socket_released);
}