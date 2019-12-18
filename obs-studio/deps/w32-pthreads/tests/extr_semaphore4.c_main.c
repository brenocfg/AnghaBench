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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int MAX_COUNT ; 
 int /*<<< orphan*/  PTHREAD_PROCESS_PRIVATE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pthread_cancel (int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  s ; 
 int /*<<< orphan*/  sched_yield () ; 
 scalar_t__ sem_getvalue (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thr ; 

int
main()
{
	int value = 0;
	int i;
	pthread_t t[MAX_COUNT+1];

	assert(sem_init(&s, PTHREAD_PROCESS_PRIVATE, 0) == 0);
	assert(sem_getvalue(&s, &value) == 0);
	assert(value == 0);

	for (i = 1; i <= MAX_COUNT; i++)
		{
			assert(pthread_create(&t[i], NULL, thr, NULL) == 0);
			do {
			  sched_yield();
			  assert(sem_getvalue(&s, &value) == 0);
			} while (value != -i);
			assert(-value == i);
		}

	assert(sem_getvalue(&s, &value) == 0);
	assert(-value == MAX_COUNT);
	assert(pthread_cancel(t[50]) == 0);
	  {
	    void* result;
	    assert(pthread_join(t[50], &result) == 0);
	  }
	assert(sem_getvalue(&s, &value) == 0);
	assert(-value == (MAX_COUNT - 1));

	for (i = MAX_COUNT - 2; i >= 0; i--)
		{
			assert(sem_post(&s) == 0);
			assert(sem_getvalue(&s, &value) == 0);
			assert(-value == i);
		}

	for (i = 1; i <= MAX_COUNT; i++)
	  if (i != 50)
	    assert(pthread_join(t[i], NULL) == 0);

  return 0;
}