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
struct snd_seq_fifo {scalar_t__ cells; int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; int /*<<< orphan*/  overflow; int /*<<< orphan*/  input_sleep; int /*<<< orphan*/  use_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/ * pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct snd_seq_fifo*) ; 
 struct snd_seq_fifo* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_pool_delete (int /*<<< orphan*/ **) ; 
 scalar_t__ snd_seq_pool_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * snd_seq_pool_new (int) ; 
 int /*<<< orphan*/  snd_use_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct snd_seq_fifo *snd_seq_fifo_new(int poolsize)
{
	struct snd_seq_fifo *f;

	f = kzalloc(sizeof(*f), GFP_KERNEL);
	if (!f)
		return NULL;

	f->pool = snd_seq_pool_new(poolsize);
	if (f->pool == NULL) {
		kfree(f);
		return NULL;
	}
	if (snd_seq_pool_init(f->pool) < 0) {
		snd_seq_pool_delete(&f->pool);
		kfree(f);
		return NULL;
	}

	spin_lock_init(&f->lock);
	snd_use_lock_init(&f->use_lock);
	init_waitqueue_head(&f->input_sleep);
	atomic_set(&f->overflow, 0);

	f->head = NULL;
	f->tail = NULL;
	f->cells = 0;
	
	return f;
}