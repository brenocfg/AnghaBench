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
typedef  int /*<<< orphan*/  LPLONG ;
typedef  scalar_t__ LONG ;

/* Variables and functions */
 scalar_t__ InterlockedIncrement (int /*<<< orphan*/ ) ; 
 int PTHREAD_BARRIER_SERIAL_THREAD ; 
 int /*<<< orphan*/  barrier ; 
 char** error_string ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int pthread_barrier_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  totalThreadCrossings ; 

void *
func(void * crossings)
{
  int result;
  int serialThreads = 0;

  while ((LONG)(size_t)crossings >= (LONG)InterlockedIncrement((LPLONG)&totalThreadCrossings))
    {
      result = pthread_barrier_wait(&barrier);

      if (result == PTHREAD_BARRIER_SERIAL_THREAD)
        {
          serialThreads++;
        }
      else if (result != 0)
        {
          printf("Barrier failed: result = %s\n", error_string[result]);
          fflush(stdout);
          return NULL;
        }
    }

  return (void*)(size_t)serialThreads;
}