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
 scalar_t__ GetDurationMilliSecs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTW32_FTIME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  currSysTimeStart ; 
 int /*<<< orphan*/  currSysTimeStop ; 
 int /*<<< orphan*/  lock ; 
 scalar_t__ pthread_spin_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_spin_unlock (int /*<<< orphan*/ *) ; 
 int washere ; 

void * func(void * arg)
{
  PTW32_FTIME(&currSysTimeStart);
  washere = 1;
  assert(pthread_spin_lock(&lock) == 0);
  assert(pthread_spin_unlock(&lock) == 0);
  PTW32_FTIME(&currSysTimeStop);

  return (void *)(size_t)GetDurationMilliSecs(currSysTimeStart, currSysTimeStop);
}