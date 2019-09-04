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
 int EAGAIN ; 
 int /*<<< orphan*/  PTHREAD_PROCESS_PRIVATE ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 char** error_string ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sem_post (int /*<<< orphan*/ *) ; 
 int sem_trywait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 

void *
thr(void * arg)
{
  sem_t s;
  int result;

  assert(sem_init(&s, PTHREAD_PROCESS_PRIVATE, 0) == 0);

  assert((result = sem_trywait(&s)) == -1);

  if ( result == -1 )
  {
    int err = errno;
    if (err != EAGAIN)
    {
      printf("thread: sem_trywait 1: expecting error %s: got %s\n",
	     error_string[EAGAIN], error_string[err]); fflush(stdout);
    }
    assert(err == EAGAIN);
  }
  else
  {
    printf("thread: ok 1\n");
  }

  assert((result = sem_post(&s)) == 0);

  assert((result = sem_trywait(&s)) == 0);

  assert(sem_post(&s) == 0);

  return NULL;
}