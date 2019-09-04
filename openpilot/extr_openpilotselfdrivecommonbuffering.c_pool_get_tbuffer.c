#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t num_tbufs; int stopped; int /*<<< orphan*/  lock; int /*<<< orphan*/  num_bufs; int /*<<< orphan*/ * tbufs; } ;
typedef  int /*<<< orphan*/  TBuffer ;
typedef  TYPE_1__ Pool ;

/* Variables and functions */
 size_t POOL_MAX_TBUFS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pool_release ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tbuffer_init2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,void (*) (void*,int),TYPE_1__*) ; 
 int /*<<< orphan*/  tbuffer_stop (int /*<<< orphan*/ *) ; 

TBuffer* pool_get_tbuffer(Pool *s) {
  pthread_mutex_lock(&s->lock);

  assert(s->num_tbufs < POOL_MAX_TBUFS);
  TBuffer* tbuf = &s->tbufs[s->num_tbufs];
  s->num_tbufs++;
  tbuffer_init2(tbuf, s->num_bufs,
                "pool", (void (*)(void *, int))pool_release, s);

  bool stopped = s->stopped;
  pthread_mutex_unlock(&s->lock);

  // Stop the tbuffer so we can return a valid object.
  // We must stop here because the pool_stop may have already been called,
  // in which case tbuffer_stop may never be called again.
  if (stopped) {
    tbuffer_stop(tbuf);
  }
  return tbuf;
}