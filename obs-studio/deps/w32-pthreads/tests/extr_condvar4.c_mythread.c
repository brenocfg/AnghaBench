#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  notbusy; int /*<<< orphan*/  lock; int /*<<< orphan*/  shared; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ cvthing ; 
 scalar_t__ pthread_cond_signal (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void *
mythread(void * arg)
{
  assert(pthread_mutex_lock(&cvthing.lock) == 0);
  cvthing.shared++;
  assert(pthread_mutex_unlock(&cvthing.lock) == 0);

  assert(pthread_cond_signal(&cvthing.notbusy) == 0);

  return (void *) 0;
}