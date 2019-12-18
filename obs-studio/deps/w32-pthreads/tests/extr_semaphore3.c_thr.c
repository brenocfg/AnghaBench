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
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pthread_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  s ; 
 scalar_t__ sem_wait (int /*<<< orphan*/ *) ; 

void *
thr (void * arg)
{
  assert(sem_wait(&s) == 0);
  assert(pthread_detach(pthread_self()) == 0);
  return NULL;
}