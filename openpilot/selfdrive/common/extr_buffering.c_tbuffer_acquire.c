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
struct TYPE_3__ {int pending_idx; int num_bufs; int* reading; int /*<<< orphan*/  lock; int /*<<< orphan*/  efd; scalar_t__ stopped; int /*<<< orphan*/  cv; } ;
typedef  TYPE_1__ TBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  efd_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int tbuffer_acquire(TBuffer *tb) {
  pthread_mutex_lock(&tb->lock);

  if (tb->stopped) {
    pthread_mutex_unlock(&tb->lock);
    return -1;
  }

  while (tb->pending_idx == -1) {
    pthread_cond_wait(&tb->cv, &tb->lock);

    if (tb->stopped) {
      pthread_mutex_unlock(&tb->lock);
      return -1;
    }
  }

  efd_clear(tb->efd);

  int ret = tb->pending_idx;
  assert(ret < tb->num_bufs);

  tb->reading[ret] = true;
  tb->pending_idx = -1;

  pthread_mutex_unlock(&tb->lock);

  return ret;
}