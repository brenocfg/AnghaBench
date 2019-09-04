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
struct snd_seq_queue {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int SNDRV_SEQ_MAX_QUEUES ; 
 int /*<<< orphan*/  queuefree (struct snd_seq_queue*) ; 
 struct snd_seq_queue* queueptr (int) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

struct snd_seq_queue *snd_seq_queue_find_name(char *name)
{
	int i;
	struct snd_seq_queue *q;

	for (i = 0; i < SNDRV_SEQ_MAX_QUEUES; i++) {
		if ((q = queueptr(i)) != NULL) {
			if (strncmp(q->name, name, sizeof(q->name)) == 0)
				return q;
			queuefree(q);
		}
	}
	return NULL;
}