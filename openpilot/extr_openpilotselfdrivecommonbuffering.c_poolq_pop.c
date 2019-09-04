#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t head; size_t tail; int* idx; int num; int num_bufs; int /*<<< orphan*/  lock; int /*<<< orphan*/  efd; scalar_t__ stopped; int /*<<< orphan*/  cv; } ;
typedef  TYPE_1__ PoolQueue ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  efd_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int poolq_pop(PoolQueue *c) {
  pthread_mutex_lock(&c->lock);

  if (c->stopped) {
    pthread_mutex_unlock(&c->lock);
    return -1;
  }

  while (c->head == c->tail) {
    pthread_cond_wait(&c->cv, &c->lock);

    if (c->stopped) {
      pthread_mutex_unlock(&c->lock);
      return -1;
    }
  }

  // printf("pop head %d tail %d\n", s->head, s->tail);

  assert(c->head != c->tail);

  int r = c->idx[c->tail];
  c->idx[c->tail] = -1;
  c->tail = (c->tail+1) % c->num;

  // queue event is level triggered
  if (c->head == c->tail) {
    efd_clear(c->efd);
  }

  // printf("pop %d head %d tail %d\n", r, s->head, s->tail);

  assert(r >= 0 && r < c->num_bufs);

  pthread_mutex_unlock(&c->lock);

  return r;
}