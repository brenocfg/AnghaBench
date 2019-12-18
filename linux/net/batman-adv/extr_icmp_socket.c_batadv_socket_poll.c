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
struct file {struct batadv_socket_client* private_data; } ;
struct batadv_socket_client {scalar_t__ queue_len; int /*<<< orphan*/  queue_wait; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t batadv_socket_poll(struct file *file, poll_table *wait)
{
	struct batadv_socket_client *socket_client = file->private_data;

	poll_wait(file, &socket_client->queue_wait, wait);

	if (socket_client->queue_len > 0)
		return EPOLLIN | EPOLLRDNORM;

	return 0;
}