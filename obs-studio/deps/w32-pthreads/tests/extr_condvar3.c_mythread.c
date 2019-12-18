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
 int /*<<< orphan*/  cv ; 
 char** error_string ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int pthread_cond_signal (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shared ; 

void *
mythread(void * arg)
{
  int result = 0;

  assert(pthread_mutex_lock(&mutex) == 0);
  shared++;
  assert(pthread_mutex_unlock(&mutex) == 0);

  if ((result = pthread_cond_signal(&cv)) != 0)
    {
      printf("Error = %s\n", error_string[result]);
    }
  assert(result == 0);


  return (void *) 0;
}