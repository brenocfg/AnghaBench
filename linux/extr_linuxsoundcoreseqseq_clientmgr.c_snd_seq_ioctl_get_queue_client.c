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
struct snd_seq_queue_client {int used; int /*<<< orphan*/  client; int /*<<< orphan*/  queue; } ;
struct snd_seq_client {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int EINVAL ; 
 int snd_seq_queue_is_used (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_seq_ioctl_get_queue_client(struct snd_seq_client *client,
					  void *arg)
{
	struct snd_seq_queue_client *info = arg;
	int used;

	used = snd_seq_queue_is_used(info->queue, client->number);
	if (used < 0)
		return -EINVAL;
	info->used = used;
	info->client = client->number;

	return 0;
}