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
struct snd_seq_event {scalar_t__ type; TYPE_1__ source; } ;
struct snd_seq_client {int /*<<< orphan*/  ioctl_mutex; int /*<<< orphan*/  accept_output; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ SNDRV_SEQ_EVENT_KERNEL_ERROR ; 
 scalar_t__ SNDRV_SEQ_EVENT_NONE ; 
 scalar_t__ check_event_type_and_length (struct snd_seq_event*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_seq_client_enqueue_event (struct snd_seq_client*,struct snd_seq_event*,struct file*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_seq_client_unlock (struct snd_seq_client*) ; 
 struct snd_seq_client* snd_seq_client_use_ptr (int) ; 

int snd_seq_kernel_client_enqueue(int client, struct snd_seq_event *ev,
				  struct file *file, bool blocking)
{
	struct snd_seq_client *cptr;
	int result;

	if (snd_BUG_ON(!ev))
		return -EINVAL;

	if (ev->type == SNDRV_SEQ_EVENT_NONE)
		return 0; /* ignore this */
	if (ev->type == SNDRV_SEQ_EVENT_KERNEL_ERROR)
		return -EINVAL; /* quoted events can't be enqueued */

	/* fill in client number */
	ev->source.client = client;

	if (check_event_type_and_length(ev))
		return -EINVAL;

	cptr = snd_seq_client_use_ptr(client);
	if (cptr == NULL)
		return -EINVAL;
	
	if (!cptr->accept_output) {
		result = -EPERM;
	} else { /* send it */
		mutex_lock(&cptr->ioctl_mutex);
		result = snd_seq_client_enqueue_event(cptr, ev, file, blocking,
						      false, 0,
						      &cptr->ioctl_mutex);
		mutex_unlock(&cptr->ioctl_mutex);
	}

	snd_seq_client_unlock(cptr);
	return result;
}