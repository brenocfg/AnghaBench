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
struct snd_seq_client {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 struct snd_seq_client* clientptr (int) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  kfree (struct snd_seq_client*) ; 
 int /*<<< orphan*/  seq_free_client (struct snd_seq_client*) ; 
 scalar_t__ snd_BUG_ON (int /*<<< orphan*/ ) ; 

int snd_seq_delete_kernel_client(int client)
{
	struct snd_seq_client *ptr;

	if (snd_BUG_ON(in_interrupt()))
		return -EBUSY;

	ptr = clientptr(client);
	if (ptr == NULL)
		return -EINVAL;

	seq_free_client(ptr);
	kfree(ptr);
	return 0;
}