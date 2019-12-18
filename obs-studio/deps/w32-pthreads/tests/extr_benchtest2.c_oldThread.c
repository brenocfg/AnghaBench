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
 int /*<<< orphan*/  old_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  old_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ox1 ; 
 int /*<<< orphan*/  ox2 ; 
 scalar_t__ running ; 
 int /*<<< orphan*/  sched_yield () ; 

void *
oldThread(void * arg)
{
  do
    {
      (void) old_mutex_lock(&ox1);
      (void) old_mutex_lock(&ox2);
      (void) old_mutex_unlock(&ox1);
      sched_yield();
      (void) old_mutex_unlock(&ox2);
    }
  while (running);

  return NULL;
}