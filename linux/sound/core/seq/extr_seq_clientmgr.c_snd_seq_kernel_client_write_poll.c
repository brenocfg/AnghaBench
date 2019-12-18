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
struct snd_seq_client {int /*<<< orphan*/  pool; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 int ENXIO ; 
 struct snd_seq_client* clientptr (int) ; 
 scalar_t__ snd_seq_pool_poll_wait (int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_seq_write_pool_allocated (struct snd_seq_client*) ; 

int snd_seq_kernel_client_write_poll(int clientid, struct file *file, poll_table *wait)
{
	struct snd_seq_client *client;

	client = clientptr(clientid);
	if (client == NULL)
		return -ENXIO;

	if (! snd_seq_write_pool_allocated(client))
		return 1;
	if (snd_seq_pool_poll_wait(client->pool, file, wait))
		return 1;
	return 0;
}