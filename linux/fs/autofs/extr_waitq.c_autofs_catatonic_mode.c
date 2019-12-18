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
struct TYPE_2__ {int /*<<< orphan*/ * name; } ;
struct autofs_wait_queue {int /*<<< orphan*/  queue; int /*<<< orphan*/  wait_ctr; TYPE_1__ name; int /*<<< orphan*/  status; struct autofs_wait_queue* next; } ;
struct autofs_sb_info {int flags; int pipefd; int /*<<< orphan*/  wq_mutex; int /*<<< orphan*/ * pipe; struct autofs_wait_queue* queues; } ;

/* Variables and functions */
 int AUTOFS_SBI_CATATONIC ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void autofs_catatonic_mode(struct autofs_sb_info *sbi)
{
	struct autofs_wait_queue *wq, *nwq;

	mutex_lock(&sbi->wq_mutex);
	if (sbi->flags & AUTOFS_SBI_CATATONIC) {
		mutex_unlock(&sbi->wq_mutex);
		return;
	}

	pr_debug("entering catatonic mode\n");

	sbi->flags |= AUTOFS_SBI_CATATONIC;
	wq = sbi->queues;
	sbi->queues = NULL;	/* Erase all wait queues */
	while (wq) {
		nwq = wq->next;
		wq->status = -ENOENT; /* Magic is gone - report failure */
		kfree(wq->name.name);
		wq->name.name = NULL;
		wq->wait_ctr--;
		wake_up_interruptible(&wq->queue);
		wq = nwq;
	}
	fput(sbi->pipe);	/* Close the pipe */
	sbi->pipe = NULL;
	sbi->pipefd = -1;
	mutex_unlock(&sbi->wq_mutex);
}