#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int num_bufs; scalar_t__* refcnt; int num_tbufs; int /*<<< orphan*/ * tbufs; int /*<<< orphan*/  lock; TYPE_1__* queues; int /*<<< orphan*/  counter; int /*<<< orphan*/ * ts; } ;
struct TYPE_4__ {int head; int num; int tail; int* idx; int /*<<< orphan*/  cv; int /*<<< orphan*/  efd; int /*<<< orphan*/  lock; int /*<<< orphan*/  inited; } ;
typedef  TYPE_1__ PoolQueue ;
typedef  TYPE_2__ Pool ;

/* Variables and functions */
 int POOL_MAX_QUEUES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  efd_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tbuffer_dispatch (int /*<<< orphan*/ *,int) ; 

void pool_push(Pool *s, int idx) {
  pthread_mutex_lock(&s->lock);

  // printf("push %d head %d tail %d\n", idx, s->head, s->tail);

  assert(idx >= 0 && idx < s->num_bufs);

  s->ts[idx] = s->counter;
  s->counter++;

  assert(s->refcnt[idx] > 0);
  s->refcnt[idx]--; //push is a implcit release

  int num_tbufs = s->num_tbufs;
  s->refcnt[idx] += num_tbufs;

  // dispatch pool queues
  for (int i=0; i<POOL_MAX_QUEUES; i++) {
    PoolQueue *c = &s->queues[i];
    if (!c->inited) continue;
    
    pthread_mutex_lock(&c->lock);
    if (((c->head+1) % c->num) == c->tail) {
      // queue is full. skip for now
      pthread_mutex_unlock(&c->lock);
      continue;
    }

    s->refcnt[idx]++;

    c->idx[c->head] = idx;
    c->head = (c->head+1) % c->num;
    assert(c->head != c->tail);
    pthread_mutex_unlock(&c->lock);

    efd_write(c->efd);
    pthread_cond_signal(&c->cv);
  }

  pthread_mutex_unlock(&s->lock);

  for (int i=0; i<num_tbufs; i++) {
    tbuffer_dispatch(&s->tbufs[i], idx);
  }
}