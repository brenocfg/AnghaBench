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
struct TYPE_3__ {int num_bufs; scalar_t__* refcnt; int* ts; int counter; int /*<<< orphan*/  lock; int /*<<< orphan*/  cb_cookie; int /*<<< orphan*/  (* release_cb ) (int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_1__ Pool ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

int pool_select(Pool *s) {
  pthread_mutex_lock(&s->lock);

  int i;
  for (i=0; i<s->num_bufs; i++) {
    if (s->refcnt[i] == 0) {
      break;
    }
  }

  if (i >= s->num_bufs) {
    // overwrite the oldest
    // still being using in a queue or tbuffer :/

    int min_k = 0;
    int min_ts = s->ts[0];
    for (int k=1; k<s->num_bufs; k++) {
      if (s->ts[k] < min_ts) {
        min_ts = s->ts[k];
        min_k = k;
      }
    }
    i = min_k;
    printf("pool is full! evicted %d\n", min_k);

    // might be really bad if the user is doing pointery stuff
    if (s->release_cb) {
      s->release_cb(s->cb_cookie, min_k);
    }
  }

  s->refcnt[i]++;

  s->ts[i] = s->counter;
  s->counter++;

  pthread_mutex_unlock(&s->lock);

  return i;
}