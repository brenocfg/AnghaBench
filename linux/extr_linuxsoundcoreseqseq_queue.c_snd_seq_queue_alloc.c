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
struct snd_seq_queue {unsigned int info_flags; int /*<<< orphan*/  use_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct snd_seq_queue* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delete (struct snd_seq_queue*) ; 
 scalar_t__ queue_list_add (struct snd_seq_queue*) ; 
 struct snd_seq_queue* queue_new (int,int) ; 
 int /*<<< orphan*/  queue_use (struct snd_seq_queue*,int,int) ; 
 int /*<<< orphan*/  snd_use_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_use_lock_use (int /*<<< orphan*/ *) ; 

struct snd_seq_queue *snd_seq_queue_alloc(int client, int locked, unsigned int info_flags)
{
	struct snd_seq_queue *q;

	q = queue_new(client, locked);
	if (q == NULL)
		return ERR_PTR(-ENOMEM);
	q->info_flags = info_flags;
	queue_use(q, client, 1);
	snd_use_lock_use(&q->use_lock);
	if (queue_list_add(q) < 0) {
		snd_use_lock_free(&q->use_lock);
		queue_delete(q);
		return ERR_PTR(-ENOMEM);
	}
	return q;
}