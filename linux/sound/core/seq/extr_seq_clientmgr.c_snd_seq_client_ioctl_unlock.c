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
struct snd_seq_client {int /*<<< orphan*/  ioctl_mutex; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_seq_client_unlock (struct snd_seq_client*) ; 
 struct snd_seq_client* snd_seq_client_use_ptr (int) ; 

void snd_seq_client_ioctl_unlock(int clientid)
{
	struct snd_seq_client *client;

	client = snd_seq_client_use_ptr(clientid);
	if (WARN_ON(!client))
		return;
	mutex_unlock(&client->ioctl_mutex);
	/* The doubly unrefs below are intentional; the first one releases the
	 * leftover from snd_seq_client_ioctl_lock() above, and the second one
	 * is for releasing snd_seq_client_use_ptr() in this function
	 */
	snd_seq_client_unlock(client);
	snd_seq_client_unlock(client);
}