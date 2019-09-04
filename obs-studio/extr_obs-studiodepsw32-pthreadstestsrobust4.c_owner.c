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
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lockCount ; 
 int /*<<< orphan*/ * mutex ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 

void * owner(void * arg)
{
  assert(pthread_mutex_lock(&mutex[0]) == 0);
  lockCount++;
  assert(pthread_mutex_lock(&mutex[1]) == 0);
  lockCount++;
  assert(pthread_mutex_lock(&mutex[2]) == 0);
  lockCount++;
  Sleep(200);

  return 0;
}