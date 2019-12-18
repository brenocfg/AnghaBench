#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  q; int /*<<< orphan*/  cv; } ;
struct TYPE_7__ {void* data; } ;
typedef  TYPE_1__ QueueEntry ;
typedef  TYPE_2__ Queue ;

/* Variables and functions */
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void* queue_pop(Queue *q) {
  pthread_mutex_lock(&q->lock);
  while (TAILQ_EMPTY(&q->q)) {
    pthread_cond_wait(&q->cv, &q->lock);
  }
  QueueEntry *entry = TAILQ_FIRST(&q->q);
  TAILQ_REMOVE(&q->q, entry, entries);
  pthread_mutex_unlock(&q->lock);

  void* r = entry->data;
  free(entry);
  return r;
}