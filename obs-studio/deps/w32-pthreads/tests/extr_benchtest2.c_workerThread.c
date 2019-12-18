#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  gate1 ; 
 int /*<<< orphan*/  gate2 ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ running ; 
 int /*<<< orphan*/  sched_yield () ; 

void *
workerThread(void * arg)
{
  do
    {
      (void) pthread_mutex_lock(&gate1);
      (void) pthread_mutex_lock(&gate2);
      (void) pthread_mutex_unlock(&gate1);
      sched_yield();
      (void) pthread_mutex_unlock(&gate2);
    }
  while (running);

  return NULL;
}