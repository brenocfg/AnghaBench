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
 scalar_t__ ETIMEDOUT ; 
 int /*<<< orphan*/  abstime ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pthread_rwlock_timedrdlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock1 ; 

void * rdfunc(void * arg)
{
  int ba = 0;

  assert(pthread_rwlock_timedrdlock(&rwlock1, &abstime) == ETIMEDOUT);

  return ((void *)(size_t)ba);
}