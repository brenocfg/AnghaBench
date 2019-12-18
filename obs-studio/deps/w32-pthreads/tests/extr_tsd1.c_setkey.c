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
 int* accesscount ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  key ; 
 void* pthread_getspecific (int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_setspecific (int /*<<< orphan*/ ,void*) ; 
 int* thread_set ; 

__attribute__((used)) static void
setkey(void * arg)
{
  int * j = (int *) arg;

  thread_set[j - accesscount] = 1;

  assert(*j == 0);

  assert(pthread_getspecific(key) == NULL);

  assert(pthread_setspecific(key, arg) == 0);
  assert(pthread_setspecific(key, arg) == 0);
  assert(pthread_setspecific(key, arg) == 0);

  assert(pthread_getspecific(key) == arg);

  (*j)++;

  assert(*j == 1);
}