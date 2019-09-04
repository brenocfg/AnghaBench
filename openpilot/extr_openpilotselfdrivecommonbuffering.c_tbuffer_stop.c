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
struct TYPE_3__ {int stopped; int /*<<< orphan*/  lock; int /*<<< orphan*/  cv; int /*<<< orphan*/  efd; } ;
typedef  TYPE_1__ TBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  efd_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void tbuffer_stop(TBuffer *tb) {
  pthread_mutex_lock(&tb->lock);
  tb->stopped = true;
  efd_write(tb->efd);
  pthread_cond_signal(&tb->cv);
  pthread_mutex_unlock(&tb->lock);
}