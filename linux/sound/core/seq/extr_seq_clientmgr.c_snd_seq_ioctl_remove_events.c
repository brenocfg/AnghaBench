#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_seq_remove_events {int remove_mode; } ;
struct TYPE_3__ {scalar_t__ fifo; } ;
struct TYPE_4__ {TYPE_1__ user; } ;
struct snd_seq_client {scalar_t__ type; int /*<<< orphan*/  number; TYPE_2__ data; } ;

/* Variables and functions */
 int SNDRV_SEQ_REMOVE_INPUT ; 
 int SNDRV_SEQ_REMOVE_OUTPUT ; 
 scalar_t__ USER_CLIENT ; 
 int /*<<< orphan*/  snd_seq_fifo_clear (scalar_t__) ; 
 int /*<<< orphan*/  snd_seq_queue_remove_cells (int /*<<< orphan*/ ,struct snd_seq_remove_events*) ; 

__attribute__((used)) static int snd_seq_ioctl_remove_events(struct snd_seq_client *client,
				       void *arg)
{
	struct snd_seq_remove_events *info = arg;

	/*
	 * Input mostly not implemented XXX.
	 */
	if (info->remove_mode & SNDRV_SEQ_REMOVE_INPUT) {
		/*
		 * No restrictions so for a user client we can clear
		 * the whole fifo
		 */
		if (client->type == USER_CLIENT && client->data.user.fifo)
			snd_seq_fifo_clear(client->data.user.fifo);
	}

	if (info->remove_mode & SNDRV_SEQ_REMOVE_OUTPUT)
		snd_seq_queue_remove_cells(client->number, info);

	return 0;
}