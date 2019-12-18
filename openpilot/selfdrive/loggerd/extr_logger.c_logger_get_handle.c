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
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  refcnt; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; TYPE_2__* cur_handle; } ;
typedef  TYPE_1__ LoggerState ;
typedef  TYPE_2__ LoggerHandle ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

LoggerHandle* logger_get_handle(LoggerState *s) {
  pthread_mutex_lock(&s->lock);
  LoggerHandle* h = s->cur_handle;
  if (h) {
    pthread_mutex_lock(&h->lock);
    h->refcnt++;
    pthread_mutex_unlock(&h->lock);
  }
  pthread_mutex_unlock(&s->lock);
  return h;
}