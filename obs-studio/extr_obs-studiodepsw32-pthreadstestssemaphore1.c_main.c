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
 int EAGAIN ; 
 int /*<<< orphan*/  PTHREAD_PROCESS_PRIVATE ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 char** error_string ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 
 scalar_t__ sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sem_post (int /*<<< orphan*/ *) ; 
 int sem_trywait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  thr ; 

int
main()
{
  pthread_t t;
  sem_t s;
  void* result1 = (void*)-1;
  int result2;

  assert(pthread_create(&t, NULL, thr, NULL) == 0);
  assert(pthread_join(t, &result1) == 0);
  assert((int)(size_t)result1 == 0);

  assert(sem_init(&s, PTHREAD_PROCESS_PRIVATE, 0) == 0);

  assert((result2 = sem_trywait(&s)) == -1);

  if (result2 == -1)
  {
    int err = errno;
    if (err != EAGAIN)
    {
      printf("main: sem_trywait 1: expecting error %s: got %s\n",
	     error_string[EAGAIN], error_string[err]); fflush(stdout);
    }
    assert(err == EAGAIN);
  }
  else
  {
    printf("main: ok 1\n");
  }

  assert((result2 = sem_post(&s)) == 0);

  assert((result2 = sem_trywait(&s)) == 0);

  assert(sem_post(&s) == 0);

  return 0;
}