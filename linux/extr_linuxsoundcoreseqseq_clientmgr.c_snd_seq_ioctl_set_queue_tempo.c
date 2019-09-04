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
struct snd_seq_queue_tempo {int dummy; } ;
struct snd_seq_client {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int snd_seq_set_queue_tempo (int /*<<< orphan*/ ,struct snd_seq_queue_tempo*) ; 

__attribute__((used)) static int snd_seq_ioctl_set_queue_tempo(struct snd_seq_client *client,
					 void *arg)
{
	struct snd_seq_queue_tempo *tempo = arg;
	int result;

	result = snd_seq_set_queue_tempo(client->number, tempo);
	return result < 0 ? result : 0;
}