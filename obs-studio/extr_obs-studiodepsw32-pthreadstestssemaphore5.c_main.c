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
typedef  int /*<<< orphan*/  sem_t ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_PROCESS_PRIVATE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sem_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thr ; 

int
main()
{
  pthread_t t;
  sem_t s;

  assert(sem_init(&s, PTHREAD_PROCESS_PRIVATE, 0) == 0);
  assert(pthread_create(&t, NULL, thr, (void *)&s) == 0);

  assert(sem_wait(&s) == 0);
  assert(sem_destroy(&s) == 0);

  assert(pthread_join(t, NULL) == 0);

  return 0;
}