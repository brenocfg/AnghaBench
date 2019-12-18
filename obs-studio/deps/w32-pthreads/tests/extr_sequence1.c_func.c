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
 int /*<<< orphan*/  InterlockedIncrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  done ; 
 scalar_t__ pthread_getunique_np (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  sched_yield () ; 
 int* seqmap ; 

void * func(void * arg)
{
  sched_yield();
  seqmap[(int)pthread_getunique_np(pthread_self())] = 1;
  InterlockedIncrement(&done);

  return (void *) 0; 
}