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
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cv; int /*<<< orphan*/  q; } ;
struct TYPE_7__ {void* data; } ;
typedef  TYPE_1__ QueueEntry ;
typedef  TYPE_2__ Queue ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void queue_push(Queue *q, void *data) {
  QueueEntry *entry = calloc(1, sizeof(QueueEntry));
  assert(entry);
  entry->data = data;

  pthread_mutex_lock(&q->lock);
  TAILQ_INSERT_TAIL(&q->q, entry, entries);
  pthread_cond_signal(&q->cv);
  pthread_mutex_unlock(&q->lock);
}