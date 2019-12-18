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
struct TYPE_2__ {int client; } ;
struct snd_seq_event {TYPE_1__ source; int /*<<< orphan*/  queue; } ;
struct snd_seq_client {int /*<<< orphan*/  accept_output; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  SNDRV_SEQ_QUEUE_DIRECT ; 
 scalar_t__ check_event_type_and_length (struct snd_seq_event*) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_seq_client_unlock (struct snd_seq_client*) ; 
 struct snd_seq_client* snd_seq_client_use_ptr (int) ; 
 int snd_seq_deliver_event (struct snd_seq_client*,struct snd_seq_event*,int,int) ; 

int snd_seq_kernel_client_dispatch(int client, struct snd_seq_event * ev,
				   int atomic, int hop)
{
	struct snd_seq_client *cptr;
	int result;

	if (snd_BUG_ON(!ev))
		return -EINVAL;

	/* fill in client number */
	ev->queue = SNDRV_SEQ_QUEUE_DIRECT;
	ev->source.client = client;

	if (check_event_type_and_length(ev))
		return -EINVAL;

	cptr = snd_seq_client_use_ptr(client);
	if (cptr == NULL)
		return -EINVAL;

	if (!cptr->accept_output)
		result = -EPERM;
	else
		result = snd_seq_deliver_event(cptr, ev, atomic, hop);

	snd_seq_client_unlock(cptr);
	return result;
}