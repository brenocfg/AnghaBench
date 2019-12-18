#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int num; int* idx; int inited; int /*<<< orphan*/  cv; int /*<<< orphan*/  lock; int /*<<< orphan*/  efd; TYPE_2__* pool; } ;
typedef  TYPE_1__ PoolQueue ;
typedef  TYPE_2__ Pool ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  pool_release_locked (TYPE_2__*,int) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void pool_release_queue(PoolQueue *c) {
  Pool *s = c->pool;

  pthread_mutex_lock(&s->lock);
  pthread_mutex_lock(&c->lock);

  for (int i=0; i<c->num; i++) {
    if (c->idx[i] != -1) {
      pool_release_locked(s, c->idx[i]);
    }
  }

  close(c->efd);
  free(c->idx);

  c->inited = false;

  pthread_mutex_unlock(&c->lock);

  pthread_mutex_destroy(&c->lock);
  pthread_cond_destroy(&c->cv);

  pthread_mutex_unlock(&s->lock);
}