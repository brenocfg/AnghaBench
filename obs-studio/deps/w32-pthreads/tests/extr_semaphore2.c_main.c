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

/* Variables and functions */
 int MAX_COUNT ; 
 int /*<<< orphan*/  PTHREAD_PROCESS_PRIVATE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sem_getvalue (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sem_post (int /*<<< orphan*/ *) ; 
 scalar_t__ sem_wait (int /*<<< orphan*/ *) ; 

int
main()
{
  sem_t s;
	int value = 0;
	int i;

  assert(sem_init(&s, PTHREAD_PROCESS_PRIVATE, MAX_COUNT) == 0);
	assert(sem_getvalue(&s, &value) == 0);
	assert(value == MAX_COUNT);
//	  printf("Value = %ld\n", value);

	for (i = MAX_COUNT - 1; i >= 0; i--)
		{
			assert(sem_wait(&s) == 0);
			assert(sem_getvalue(&s, &value) == 0);
//			  printf("Value = %ld\n", value);
			assert(value == i);
		}

	for (i = 1; i <= MAX_COUNT; i++)
		{
			assert(sem_post(&s) == 0);
			assert(sem_getvalue(&s, &value) == 0);
//			  printf("Value = %ld\n", value);
			assert(value == i);
		}

  return 0;
}